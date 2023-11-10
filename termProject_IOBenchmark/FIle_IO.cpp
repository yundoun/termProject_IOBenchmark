#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ���� ũ�⸦ ����Ʈ�� ��ȯ�ϴ� �Լ�
long long getFileSize(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        perror("���� ���� ����");
        exit(1);
    }

    fseek(file, 0, SEEK_END); // ���� ������ �̵�
    long long file_size = ftell(file); // ���� ũ�� ����
    fclose(file);

    return file_size;
}

int main() {
    // ���� ���� ���
    const char* local_file_path = "dummyFile"; // ���� ���� ��θ� ����

    // ��Ʈ��ũ ���� ���
    const char* network_filepath = "\\\\DESKTOP-3AOVSUA\\dummyFile\\dummyFile2"; // ��Ʈ��ũ ���� ��θ� ����

    // ���� ���� ũ�� ���
    long long local_file_size = getFileSize(local_file_path);
    printf("���� ������ ũ��: %lld bytes\n\n", local_file_size);

    // ��Ʈ��ũ ���� ũ�� ���
    long long network_file_size = getFileSize(network_filepath);
    printf("��Ʈ��ũ ������ ũ��: %lld bytes\n\n", network_file_size);

    // ��� ũ�⸦ 100B, 8KB, 32KB, 64KB, 256KB�� ����
    int block_sizes[] = { 100, 8192, 32768, 65536, 262144 };

    // ���� ������ ���� ���� ����
    FILE* local_file = fopen(local_file_path, "rb");
    if (local_file == NULL) {
        perror("���� ���� ���� ����");
        return 1;
    }

    // ��Ʈ��ũ ������ ���� ���� ����
    FILE* network_file = fopen(network_filepath, "rb");
    if (network_file == NULL) {
        perror("��Ʈ��ũ ���� ���� ����");
        return 1;
    }

    // ����� ����ϱ� ���� ���
    printf("��� ũ�� (Bytes)\t���� ���� �б� �ð� (ms)\t��Ʈ��ũ ���� �б� �ð� (ms)\n");

    for (int i = 0; i < sizeof(block_sizes) / sizeof(block_sizes[0]); i++) {
        int block_size = block_sizes[i];

        // ���� ���� �Ҵ�
        char* buffer = (char*)malloc(block_size);
        if (buffer == NULL) {
            perror("�޸� �Ҵ� ����");
            return 1;
        }

        size_t bytes_read;
        clock_t start_time, end_time;

        // ���� ���� �б� �ð� ���� ����
        start_time = clock();

        // ���� ���Ͽ��� ������ �б�
        while ((bytes_read = fread(buffer, 1, block_size, local_file)) > 0) {
            // ���� �����͸� ���⼭ ó���� �� �ֽ��ϴ�.
        }

        // ���� ���� �б� �ð� ���� ����
        end_time = clock();
        double local_elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000; // �и��ʷ� ��ȯ

        // ��Ʈ��ũ ���� �б� �ð� ���� ����
        start_time = clock();

        // ��Ʈ��ũ ���Ͽ��� ������ �б�
        while ((bytes_read = fread(buffer, 1, block_size, network_file)) > 0) {
            // ���� �����͸� ���⼭ ó���� �� �ֽ��ϴ�.
        }

        // ��Ʈ��ũ ���� �б� �ð� ���� ����
        end_time = clock();
        double network_elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000; // �и��ʷ� ��ȯ

        // ��� ���
        printf("%d\t\t\t%.2f\t\t\t\t%.2f\n", block_size, local_elapsed_time, network_elapsed_time);

        free(buffer); // ���� �Ҵ�� ���� �޸� ����
        fseek(local_file, 0, SEEK_SET); // ���� ���� �����͸� ������ �������� �̵�
        fseek(network_file, 0, SEEK_SET); // ��Ʈ��ũ ���� �����͸� ������ �������� �̵�
    }

    // ���� �ݱ�
    fclose(local_file);
    fclose(network_file);

    printf("\n");
    printf("�ü�� termProject - 20193066 ������\n");
    return 0;
}