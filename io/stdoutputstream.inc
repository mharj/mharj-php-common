<?php
namespace io;

class StdOutputStream extends OutputStream {
	private $fd = null;
	
	public function __construct() {
		if ( php_sapi_name() === 'cli' ) {
			$this->fd = @fopen('php://stdout','w');
			if ( $this->fd == false ) {
				throw new IOException("Can't open stdout");
			}
		} 
	}
	
	public function write($data) {
		if ( php_sapi_name() === 'cli' ) {
			if ( fwrite( $this->fd , $data ) === false ) {
				throw new IOException("Can't write to stdout");
			}
		} else {
			echo $data;
		}
	}
	
	public function flush() {
		if ( php_sapi_name() === 'cli' ) {
			if ( fflush( $this->fd) === false ) {
				throw new IOException("Can't flush stdout");
			}
		} else {
			flush();
		}
	}
	
}