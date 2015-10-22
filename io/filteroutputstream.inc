<?php
namespace io;

class FilterOutputStream extends OutputStream {
	protected $out;
	public function __construct(OutputStream $out) {
		$this->out = $out;
	}

	public function write($data) {
		$this->out->write($data);
	}
	
	public function flush() {
		$this->out->flush();
	}
	
	public function close() {
		try {
			$this->flush();
		} catch (IOException $ex) {
		}
		$this->out->close();
	}
}