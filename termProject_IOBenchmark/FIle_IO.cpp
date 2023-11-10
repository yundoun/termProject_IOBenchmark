#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 파일 크기를 바이트로 반환하는 함수
long long getFileSize(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        perror("파일 열기 실패");
        exit(1);
    }

    fseek(file, 0, SEEK_END); // 파일 끝으로 이동
    long long file_size = ftell(file); // 파일 크기 측정
    fclose(file);

    return file_size;
}

int main() {
    // 로컬 파일 경로
    const char* local_file_path = "dummyFile"; // 로컬 파일 경로를 지정

    // 네트워크 파일 경로
    const char* network_filepath = "\\\\DESKTOP-3AOVSUA\\dummyFile\\dummyFile2"; // 네트워크 파일 경로를 지정

    // 로컬 파일 크기 출력
    long long local_file_size = getFileSize(local_file_path);
    printf("로컬 파일의 크기: %lld bytes\n\n", local_file_size);

    // 네트워크 파일 크기 출력
    long long network_file_size = getFileSize(network_filepath);
    printf("네트워크 파일의 크기: %lld bytes\n\n", network_file_size);

    // 블록 크기를 100B, 8KB, 32KB, 64KB, 256KB로 설정
    int block_sizes[] = { 100, 8192, 32768, 65536, 262144 };

    // 로컬 파일을 읽을 모드로 열기
    FILE* local_file = fopen(local_file_path, "rb");
    if (local_file == NULL) {
        perror("로컬 파일 열기 실패");
        return 1;
    }

    // 네트워크 파일을 읽을 모드로 열기
    FILE* network_file = fopen(network_filepath, "rb");
    if (network_file == NULL) {
        perror("네트워크 파일 열기 실패");
        return 1;
    }

    // 결과를 출력하기 위한 헤더
    printf("블록 크기 (Bytes)\t로컬 파일 읽기 시간 (ms)\t네트워크 파일 읽기 시간 (ms)\n");

    for (int i = 0; i < sizeof(block_sizes) / sizeof(block_sizes[0]); i++) {
        int block_size = block_sizes[i];

        // 버퍼 동적 할당
        char* buffer = (char*)malloc(block_size);
        if (buffer == NULL) {
            perror("메모리 할당 실패");
            return 1;
        }

        size_t bytes_read;
        clock_t start_time, end_time;

        // 로컬 파일 읽기 시간 측정 시작
        start_time = clock();

        // 로컬 파일에서 데이터 읽기
        while ((bytes_read = fread(buffer, 1, block_size, local_file)) > 0) {
            // 읽은 데이터를 여기서 처리할 수 있습니다.
        }

        // 로컬 파일 읽기 시간 측정 종료
        end_time = clock();
        double local_elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000; // 밀리초로 변환

        // 네트워크 파일 읽기 시간 측정 시작
        start_time = clock();

        // 네트워크 파일에서 데이터 읽기
        while ((bytes_read = fread(buffer, 1, block_size, network_file)) > 0) {
            // 읽은 데이터를 여기서 처리할 수 있습니다.
        }

        // 네트워크 파일 읽기 시간 측정 종료
        end_time = clock();
        double network_elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000; // 밀리초로 변환

        // 결과 출력
        printf("%d\t\t\t%.2f\t\t\t\t%.2f\n", block_size, local_elapsed_time, network_elapsed_time);

        free(buffer); // 동적 할당된 버퍼 메모리 해제
        fseek(local_file, 0, SEEK_SET); // 로컬 파일 포인터를 파일의 시작으로 이동
        fseek(network_file, 0, SEEK_SET); // 네트워크 파일 포인터를 파일의 시작으로 이동
    }

    // 파일 닫기
    fclose(local_file);
    fclose(network_file);

    printf("\n");
    printf("운영체제 termProject - 20193066 윤도운\n");
    return 0;
}