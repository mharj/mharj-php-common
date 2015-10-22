<?php
namespace io;

class FileOutputStream extends OutputStream {
	private $fd = null;
	private $closed = false;
	private $append;
	
	public function __construct($fileName,$append=false) {
		$this->append = $append;
		if ( ! is_file($fileName ) )  {
			throw new FileNotFoundException();
		}
		$this->fd = @fopen($fileName,($append==false?'w':'a'));
		if ( $this->fd == false ) {
			throw new IOException("Can't open file");
		}
	}
	
	public function __destruct() {
		$this->close();
	}
	
	public function write($data) {
		if ( fwrite( $this->fd , $data ) === false ) {
			throw new IOException("Can't write to file");
		}
	}
	
	public function flush() {
		if ( fflush( $this->fd) === false ) {
			throw new IOException("Can't flush file");
		}
	}	
	
	public function close() {
		if ( $this->closed == false ) {
			if ( fclose($this->fd) === false ) {
				throw new IOException("Can't close file");
			}
			$this->closed = true;
		}
	}
}