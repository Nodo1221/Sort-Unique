#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

void printarr(char **arr, size_t n) {
    for (size_t i = 0; i < n - 1; i++) {
        printf("%s\n", arr[i]);
    }
    printf("%s\n", arr[n - 1]);
}

/// Takes pointer to array, left, mid and right
/// Right -- last elem of left arr
void merge(char **arr, int left, int mid, int right) {
    // Calculate span length
    int left_n = mid - left + 1;
    int right_n = right - mid;

    // Allocate and copy corresponding arrays with one more element for guardian
    char **left_tmp = malloc((left_n + 1) * sizeof(*arr));
    char **right_tmp = malloc((right_n + 1) * sizeof(*arr));
    memcpy(left_tmp, arr + left, left_n * sizeof(*arr));
    memcpy(right_tmp, arr + mid + 1, right_n * sizeof(*arr));

    // Iterate over the entire range, incrementing specific li and ri indicies (for each element, starting at left, all the way to right inclusive)
    for (int i = left, li = 0, ri = 0; i <= right; i++) {
        // If right overflows, always choosing left;
        // If left is ok (and smaller than right), choose from left
        if (ri >= right_n || (li < left_n && strcmp(left_tmp[li], right_tmp[ri]) <= 0)) {
            arr[i] = left_tmp[li];
            li++;
        }

        // Otherwise right
        else {
            arr[i] = right_tmp[ri];
            ri++;
        }
    }

    // Free
    free(left_tmp);
    free(right_tmp);
}

void merge_sort(char **arr, int left, int right) {
    // Until we have a one element array, left == right
    if (left == right)
        return;

    int mid = (left + right) / 2;

    // We sort both parts
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);

    // And merge
    merge(arr, left, mid, right);
}

void merge_wrap(char **arr, int n) {
    merge_sort(arr, 0, n - 1);
}

char **remove_duplicates(char **arr, size_t n, size_t *used) {
    char **no_dupes = malloc(sizeof(*arr) * n);
    no_dupes[0] = arr[0];

    *used = 1;
    for (size_t i = 1; i < n; i++) {
        if (strcmp(arr[i], arr[i - 1]) != 0) {
            no_dupes[*used] = arr[i];
            (*used)++;
        }
    }

    // no_dupes = realloc(no_dupes, used * sizeof(*no_dupes));
    return no_dupes;
}

int main() {
    char **lines = malloc(100 * sizeof(char *));
    size_t count = 0;
    size_t buffer = 100;

    // Read every line from stdin
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while ((nread = getline(&line, &len, stdin)) != -1) {
        if (nread > 0 && line[nread-1] == '\n') {
            line[nread-1] = '\0';
            --nread;
        }

        if (count >= buffer) {
            lines = realloc(lines, (count + 100) * sizeof(char *));
            buffer = count + 100;
        }

        lines[count] = malloc(nread + 1);
        strncpy(lines[count], line, nread + 1);
        count++;
    }

    free(line);

    merge_wrap(lines, count);

    size_t used = 0;
    char **no_dupes = remove_duplicates(lines, count, &used);
    
    printf("---\n");
    printarr(no_dupes, used);

    for (size_t i = 0; i < used; i++)
        free(lines[i]);

    free(lines);
    free(no_dupes);

    return 0;
}