#include <sys/iosupport.h>
#include <stdio.h>
#include <stdint.h>

// einfacher als libctru hier rein zu linken
static inline int svc_output_debug_string_raw(const char* str, int len) {
    register uint32_t r0 asm("r0") = (uint32_t)str;
    register uint32_t r1 asm("r1") = (uint32_t)len;

    asm volatile (
        "svc #0x3D"
        : "+r"(r0)
        : "r"(r1)
        : "r2", "r3", "r12", "lr", "cc", "memory"
    );

    return (int)r0;
}

static ssize_t __svc_write_str(struct _reent* r, void* fd, const char* ptr, size_t len) {
    // Unused param juckt keinen man
    (void)r;
    (void)fd;
    // PRINT THIS STRING...
    return svc_output_debug_string_raw(ptr, (int)len) >= 0 ? (ssize_t)len : -1;
}

static devoptab_t __dotab_svc = { .name = "svc", .write_r = __svc_write_str };

void __hook_outputs_to_svc(void) {
    devoptab_list[STD_OUT] = &__dotab_svc;
    devoptab_list[STD_ERR] = &__dotab_svc;
    setvbuf(stdout, NULL, _IOLBF, 0);
    setvbuf(stderr, NULL, _IOLBF, 0);
}
