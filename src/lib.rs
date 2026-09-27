unsafe extern "C" {
    fn __hook_outputs_to_svc();
}

pub fn hook_outputs_to_svc() {
	unsafe {	
		__hook_outputs_to_svc();
	}
}
