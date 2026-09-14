#include <jni.h>
#include <stdio.h>

/*
 * Resets curr to the scene currently being displayed.
 *
 * genscene() stores the NEXT scene number in curr.
 * When EXIT is pressed, decrement curr by 1 so that the
 * next launch regenerates the scene that was on screen.
 */
void exit_reset_curr(const char *base_dir)
{
    char curr_path[512];
    snprintf(curr_path, sizeof(curr_path), "%s/curr", base_dir);

    // Read current value from curr
    FILE *curr_file = fopen(curr_path, "r");
    if (!curr_file) {
        return;
    }

    int current;

    if (fscanf(curr_file, "%d", &current) != 1) {
        fclose(curr_file);
        return;
    }

    fclose(curr_file);

    // Decrement, but never go below 0
    if (current > 0) {
        current--;
    }

    // Write reset value back to curr
    curr_file = fopen(curr_path, "w");
    if (!curr_file) {
        return;
    }

    fprintf(curr_file, "%d\n", current);
    fclose(curr_file);
}


/*
 * Android JNI wrapper
 */
JNIEXPORT void JNICALL
Java_com_paralevels_rearviewmillennium_MainActivity_exitResetCurr(
        JNIEnv *env,
        jobject thiz,
        jstring base_dir_j)
{
    // Converts Java/Kotlin baseDir string to a C string
    const char *base_dir =
            (*env)->GetStringUTFChars(env, base_dir_j, 0);

    if (!base_dir)
        return;

    // Calls platform-independent reset function
    exit_reset_curr(base_dir);

    // Releases Java/Kotlin baseDir string
    (*env)->ReleaseStringUTFChars(env, base_dir_j, base_dir);
}


/*
 * iOS / Swift wrapper
 */
void exit_reset_curr_ios(const char *base_dir)
{
    // Calls platform-independent reset function
    exit_reset_curr(base_dir);
}
