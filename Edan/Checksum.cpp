uint16_t calcPackageChecksum(
    const int8_t * data, int len)
{
    const uint16_t * p = reinterpret_cast<const uint16_t *>(data);
    int size = len / 2;
    int i;
    unsigned int sum = 0;

    for (i = 0; i < size; i++) {
        sum += p[i];
    }
    if (len % 2) {
        sum += data[len - i];
    }
    while (sum >> 16) {
        sum = (sum & 0xffffUL) + (sum >> 16);
    }
    return static_cast<uint16_t>(~(sum & 0xffffUL));
}

// Usage

pkg_header.Checksum = calcPackageChecksum(
                              reinterpret_cast<const int8_t *>(package.data()),
                              package.size());
