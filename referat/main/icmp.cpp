#include "main.h"
#include "icmp.h"

int icmp(int *arr, char *destination)
{
    string text_message;
    // Create a raw socket
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0)
    {
        perror("socket() error");
        return 1;
    }

    // Set the TTL (Time To Live) of the IP packet
    int ttl = 64;
    if (setsockopt(sock, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
    {
        perror("setsockopt() error");
        return 1;
    }

    // Create an ICMP packet with data
    const int packet_size = sizeof(struct icmphdr) + data_length(arr, text_message); // additional enough bytes for data
    char packet[packet_size];
    struct icmphdr *icmp_hdr = (struct icmphdr *)packet;
    icmp_hdr->type = ICMP_ECHO; // ICMP Echo Request (type 8)
    icmp_hdr->code = 0;
    icmp_hdr->checksum = 0;
    icmp_hdr->un.echo.id = getpid(); // get protocol id
    icmp_hdr->un.echo.sequence = 0;

    int t = 0;

    char *text_message_char = new char[text_message.size()];
    for (char c : text_message)
    {
        text_message_char[t++] = c;
    }

    // Fill the data field with some content
    char *data = packet + sizeof(struct icmphdr); // указывает на первый элемент поля <data>, тк блок data идёт сразу после заголовка пакета (работа с памятью)
    sprintf(data, text_message_char);

    free(text_message_char);

    // Calculate the ICMP packet checksum - контрольная сумма
    unsigned short *buffer = (unsigned short *)packet;
    int buffer_size = packet_size / 2; // short = 2B, char = 1B
    unsigned int checksum = 0;
    for (int i = 0; i < buffer_size; i++)
    {
        checksum += buffer[i];
    }
    icmp_hdr->checksum = ~(checksum + (checksum >> 16));

    // Set the destination IP address
    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, destination, &dest_addr.sin_addr) <= 0) // проверка правильности конвертации IP из txt -> сетевой формат IP
    {
        cerr << "Invalid IP address: " << destination << endl;
        return 1;
    }

    // Send the ICMP packet
    ssize_t bytes_sent = sendto(sock, packet, packet_size, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (bytes_sent < 0)
    {
        perror("sendto() error");
        return 1;
    }

    close(sock);

    return 0;
}

int data_length(int *nums, string &str)
{
    str = to_string(nums[0]) + ", " + to_string(nums[1]) + ", " + to_string(nums[2]);
    return str.size();
}
