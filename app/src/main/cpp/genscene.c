#include <jni.h>
#include <stdio.h>
#include <stdlib.h>

#define SCENE_COUNT 171

// Offsets for scenes, the number of extra scene jumps
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
    {0, 0}, // Scene 11
    {0, 0}, // Scene 12
    {0, 0}, // Scene 13
    {0, 0}, // Scene 14
    {0, 0}, // Scene 15
    {0, 0}, // Scene 16
    {0, 0}, // Scene 17
    {0, 0}, // Scene 18
    {0, 0}, // Scene 19
    {0, 0}, // Scene 20
    {0, 0}, // Scene 21
    {0, 0}, // Scene 22
    {0, 0}, // Scene 23
    {0, 0}, // Scene 24
    {0, 0}, // Scene 25
    {2, 0}, // Scene 26
    {0, 0}, // Scene 27
    {0, 0}, // Scene 28
    {0, 0}, // Scene 29
    {0, 0}, // Scene 30
    {0, 0}, // Scene 31
    {0, 0}, // Scene 32
    {0, 0}, // Scene 33
    {0, 0}, // Scene 34
    {1, 0}, // Scene 35
    {0, 0}, // Scene 36
    {0, 0}, // Scene 37
    {0, 0}, // Scene 38
    {1, 0}, // Scene 39
    {0, 0}, // Scene 40
    {0, 0}, // Scene 41
    {1, 0}, // Scene 42
    {0, 0}, // Scene 43
    {0, 0}, // Scene 44
    {0, 0}, // Scene 45
    {0, 0}, // Scene 46
    {0, 0}, // Scene 47
    {1, 0}, // Scene 48
    {0, 0}, // Scene 49
    {1, 0}, // Scene 50
    {0, 0}, // Scene 51
    {0, 0}, // Scene 52
    {0, 0}, // Scene 53
    {1, 0}, // Scene 54
    {0, 0}, // Scene 55
    {0, 0}, // Scene 56
    {0, 0}, // Scene 57
    {0, 0}, // Scene 58
    {0, 0}, // Scene 59
    {2, 0}, // Scene 60
    {0, 0}, // Scene 61
    {0, 0}, // Scene 62
    {1, 0}, // Scene 63
    {0, 0}, // Scene 64
    {0, 0}, // Scene 65
    {0, 0}, // Scene 66
    {0, 0}, // Scene 67
    {0, 0}, // Scene 68
    {0, 0}, // Scene 69
    {0, 0}, // Scene 70
    {1, 0}, // Scene 71
    {0, 0}, // Scene 72
    {0, 0}, // Scene 73
    {0, 0}, // Scene 74
    {0, 0}, // Scene 75
    {2, 0}, // Scene 76
    {0, 0}, // Scene 77
    {0, 0}, // Scene 78
    {1, 0}, // Scene 79
    {0, 0}, // Scene 80
    {0, 0}, // Scene 81
    {0, 0}, // Scene 82
    {0, 0}, // Scene 83
    {0, 0}, // Scene 84
    {0, 0}, // Scene 85
    {0, 0}, // Scene 86
    {0, 0}, // Scene 87
    {0, 0}, // Scene 88
    {0, 0}, // Scene 89
    {1, 0}, // Scene 90
    {0, 0}, // Scene 91
    {0, 0}, // Scene 92
    {0, 0}, // Scene 93
    {0, 0}, // Scene 94
    {0, 0}, // Scene 95
    {0, 0}, // Scene 96
    {0, 0}, // Scene 97
    {0, 0}, // Scene 98
    {0, 0}, // Scene 99
    {0, 0}, // Scene 100
    {0, 0}, // Scene 101
    {0, 0}, // Scene 102
    {0, 0}, // Scene 103
    {0, 0}, // Scene 104
    {0, 0}, // Scene 105
    {1, 0}, // Scene 106
    {0, 0}, // Scene 107
    {0, 0}, // Scene 108
    {0, 0}, // Scene 109
    {0, 0}, // Scene 110
    {0, 0}, // Scene 111
    {1, 0}, // Scene 112
    {0, 0}, // Scene 113
    {0, 0}, // Scene 114
    {0, 0}, // Scene 115
    {0, 0}, // Scene 116
    {0, 0}, // Scene 117
    {0, 0}, // Scene 118
    {0, 0}, // Scene 119
    {0, 0}, // Scene 120
    {0, 0}, // Scene 121
    {0, 0}, // Scene 122
    {0, 0}, // Scene 123
    {0, 0}, // Scene 124
    {0, 0}, // Scene 125
    {1, 0}, // Scene 126
    {0, 0}, // Scene 127
    {0, 0}, // Scene 128
    {0, 0}, // Scene 129
    {0, 0}, // Scene 130
    {0, 0}, // Scene 131
    {0, 0}, // Scene 132
    {0, 0}, // Scene 133
    {0, 0}, // Scene 134
    {0, 0}, // Scene 135
    {0, 0}, // Scene 136
    {0, 0}, // Scene 137
    {0, 0}, // Scene 138
    {0, 0}, // Scene 139
    {0, 0}, // Scene 140
    {0, 0}, // Scene 141
    {0, 0}, // Scene 142
    {0, 0}, // Scene 143
    {0, 0}, // Scene 144
    {0, 0}, // Scene 145
    {0, 0}, // Scene 146
    {0, 0}, // Scene 147
    {0, 0}, // Scene 148
    {0, 0}, // Scene 149
    {0, 0}, // Scene 150
    {0, 0}, // Scene 151
    {0, 0}, // Scene 152
    {1, 0}, // Scene 153
    {0, 0}, // Scene 154
    {0, 0}, // Scene 155
    {0, 0}, // Scene 156
    {0, 0}, // Scene 157
    {0, 0}, // Scene 158
    {0, 0}, // Scene 159
    {0, 0}, // Scene 160
    {0, 0}, // Scene 161
    {0, 0}, // Scene 162
    {0, 0}, // Scene 163
    {0, 0}, // Scene 164
    {0, 0}, // Scene 165
    {0, 0}, // Scene 166
    {0, 0}, // Scene 167
    {0, 0}, // Scene 168
    {0, 0}, // Scene 169
    {0, 0}  // Scene 170
};

// JNI function called from Kotlin/Java
JNIEXPORT jstring JNICALL
Java_com_paralevels_rearviewmillennium_MainActivity_genscene(
        JNIEnv *env,
        jobject thiz,
        jstring base_dir_j,
        jint choice
) {
    // Converts Java/Kotlin baseDir string to a C string
    const char *base_dir = (*env)->GetStringUTFChars(env, base_dir_j, 0);
    if (!base_dir) {
        return (*env)->NewStringUTF(env, "ERROR\n\nBase directory missing.\n\nContinue\n\nContinue\n");
    }

    // Builds path to curr from base_dir
    char curr_path[512];
    snprintf(curr_path, sizeof(curr_path), "%s/curr", base_dir);

    // Reads current scene index from curr file
    FILE *curr_file = fopen(curr_path, "r");
    int current = -1;
    if (curr_file) {
        fscanf(curr_file, "%d", &current);
        fclose(curr_file);
    }

    // Initializes next
    int next = current + 1;

    // Adds offset to next scene based on choice
    if (current >= 0 && current < SCENE_COUNT && choice >= 0 && choice <= 1) {
        next += scene_offset[current][choice];
    }

    // Reached the end. Reset.
    if (next < 0 || next >= SCENE_COUNT) {
        next = 0;
    }

    // Builds scene_path from base_dir and next
    char scene_path[512];
    snprintf(scene_path, sizeof(scene_path), "%s/scenes/%d.scene", base_dir, next);

    // Opens scene file at scene_path, handles error
    FILE *scene_file = fopen(scene_path, "r");
    if (!scene_file) {
        (*env)->ReleaseStringUTFChars(env, base_dir_j, base_dir);
        return (*env)->NewStringUTF(env, "ERROR\n\nScene file missing.\n\nContinue\n\nContinue\n");
    }

    // Saves next scene index to curr file
    curr_file = fopen(curr_path, "w");
    if (curr_file) {
        fprintf(curr_file, "%d\n", next);
        fclose(curr_file);
    }

    // Gets scene file size
    fseek(scene_file, 0, SEEK_END);
    long size = ftell(scene_file);
    rewind(scene_file);

    // Reads scene file contents into buffer, handles error
    char *buffer = malloc(size + 1);
    if (!buffer) {
        fclose(scene_file);
        (*env)->ReleaseStringUTFChars(env, base_dir_j, base_dir);
        return (*env)->NewStringUTF(env, "ERROR\n\nMemory allocation failed.\n\nContinue\n\nContinue\n");
    }
    fread(buffer, 1, size, scene_file);
    buffer[size] = '\0';

    // Closes scene file
    fclose(scene_file);

    // Converts C buffer to Java/Kotlin string
    jstring result = (*env)->NewStringUTF(env, buffer);

    // Frees memory
    free(buffer);
    (*env)->ReleaseStringUTFChars(env, base_dir_j, base_dir);

    return result;
}