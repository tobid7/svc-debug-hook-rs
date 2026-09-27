# svc-debug-hook-rs

Redirect all stdout and stderr calls to svcOutputDebugString...

Helps debugging stuff without logfiles in Azahar/Citra.

Setting Log Filter to `*:Error Debug.Emulated:Debug` helps a lot...

```rust
fn main() {
        svc_debug_hook_rs::hook_outputs_to_svc();
        println!("Hello World... from rust btw");
}
```
