use std::env;

fn main() {
    let devkitpro = env::var("DEVKITPRO")
        .expect("Where is your defkitpro files huh?");

    cc::Build::new()
        .file("src/hook.c")
        .compiler(format!("{devkitpro}/devkitARM/bin/arm-none-eabi-gcc"))
        .archiver(format!("{devkitpro}/devkitARM/bin/arm-none-eabi-ar")) 
        .include(format!("{devkitpro}/libctru/include"))
        .flag("-march=armv6k")
        .flag("-mtune=mpcore")
        .flag("-mfloat-abi=hard")
        .flag("-mtp=soft")
        .flag("-mfpu=vfpv2")
        .compile("__hook_output_svc");
}
