#include <jni.h>
#include <stdio.h>
#include <stdlib.h>

#define SCENE_COUNT 12

int scene_offset[SCENE_COUNT][2] = {
    {0, 0}, // Scene 0
    {0, 0}, // Scene 1
    {0, 0}, // Scene 2
    {0, 0}, // Scene 3
    {0, 0}, // Scene 4
    {1, 0}, // Scene 5
    {0, 0}, // Scene 6
    {2, 0}, // Scene 7
    {0, 0}, // Scene 8
    {0, 0}, // Scene 9
    {1, 0}, // Scene 10
    {0, 0}  // Scene 11
};

JNIEXPORT jstring JNICALL
Java_com_paralevels_rearviewmillennium_MainActivity_genscene(
        JNIEnv *env,
        jobject thiz,
        jstring base_dir_j,
        jint choice
) {
    const char *base_dir = (*env)->GetStringUTFChars(env, base_dir_j, 0);

    char curr_path[512];
    snprintf(curr_path, sizeof(curr_path), "%s/curr", base_dir);

    FILE *curr_file = fopen(curr_path, "r");
    int current = -1;
    if (curr_file) {
        fscanf(curr_file, "%d", &current);
        fclose(curr_file);
    }

    int next = current + 1;

    if (current >= 0 && current < SCENE_COUNT && choice >= 0 && choice <= 1) {
        next += scene_offset[current][choice];
    }

    if (next < 0 || next >= SCENE_COUNT) {
        next = 0;
    }

    char scene_path[512];
    snprintf(scene_path, sizeof(scene_path), "%s/scenes/%d.scene", base_dir, next);

    FILE *scene_file = fopen(scene_path, "r");
    if (!scene_file) {
        (*env)->ReleaseStringUTFChars(env, base_dir_j, base_dir);
        return (*env)->NewStringUTF(env, "ERROR\n\nScene file missing.\n\nContinue\n\nContinue\n");
    }

    curr_file = fopen(curr_path, "w");
    if (curr_file) {
        fprintf(curr_file, "%d\n", next);
        fclose(curr_file);
    }

    fseek(scene_file, 0, SEEK_END);
    long size = ftell(scene_file);
    rewind(scene_file);

    char *buffer = malloc(size + 1);
    fread(buffer, 1, size, scene_file);
    buffer[size] = '\0';

    fclose(scene_file);

    jstring result = (*env)->NewStringUTF(env, buffer);

    free(buffer);
    (*env)->ReleaseStringUTFChars(env, base_dir_j, base_dir);

    return result;
}
