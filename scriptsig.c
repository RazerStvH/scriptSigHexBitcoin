#include <stdio.h>
#include <string.h>
#include <stdint.h>

void to_hex(char* dest, const uint8_t* src, size_t len) {
    static const char hex_digits[] = "0123456789ABCDEF";
    for (size_t i = 0; i < len; ++i) {
        dest[i * 2] = hex_digits[(src[i] >> 4) & 0xF];
        dest[i * 2 + 1] = hex_digits[src[i] & 0xF];
    }
    dest[len * 2] = '\0';
}

int main() {
    // Сообщение для включения в блок
    const char* pszTimestamp = "The Times 17/Nov/2024 Chancellor on brink of second bailout for banks";

    // Преобразуем сообщение в HEX
    size_t timestamp_len = strlen(pszTimestamp);
    uint8_t scriptSig[5 + timestamp_len];
    scriptSig[0] = 0x04; // Prerequisite for Coinbase transactions
    scriptSig[1] = 0xff; // More Coinbase magic bytes
    scriptSig[2] = 0xff;
    scriptSig[3] = 0x00;
    scriptSig[4] = 0x1d; // Length of the message (29 bytes in this example)

    // Копируем текст в scriptSig
    memcpy(scriptSig + 5, pszTimestamp, timestamp_len);

    // Сериализация в HEX
    char hex_scriptSig[2 * (5 + timestamp_len) + 1];
    to_hex(hex_scriptSig, scriptSig, 5 + timestamp_len);

    // Печать HEX скрипта
    printf("ScriptSig HEX: %s\n", hex_scriptSig);

    // Теперь, когда у нас есть scriptSig, вы можете строить транзакцию, добавлять публичный ключ,
    // а затем сериализовать её в HEX для дальнейшего использования.

    return 0;
}
