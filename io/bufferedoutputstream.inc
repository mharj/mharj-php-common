<?php
namespace io;

use io\FilterOutputStream;

class BufferedOutputStream extends FilterOutputStream {
	protected $buf;
	protected $limit;

	public function __construct(OutputStream $out,$size = 8192) {
		parent::__construct($out);
		$this->limit = $size;
	}
	
	public function __destruct() {
		$this->flush();
	}
	
	private function flushBuffer() {
		if ( count($this->buf) > 0 ) {
			$this->out->write($this->buf);
			$this->buf = "";
		}
	}
	
	public function write($data) {
		$this->buf .= $data;
		if ( count($this->buf) > $this->limit) {
			$this->flushBuffer();
		}
	}
	
	public function flush() {
		$this->flushBuffer();
		$this->out->flush();
	}
}
