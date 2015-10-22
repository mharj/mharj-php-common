<?php
namespace io;

class PrintStream {
	private $os;
	/**
	 * Creates a new print stream.
	 * @param \io\OutputStream $obj
	 * @throws Exception
	 */
	public function __construct($obj) { 
		if ( $obj instanceof OutputStream ) {
			$this->os = $obj;
		} else {
			throw new Exception("Unknown parameter");
		}
	}
	/**
	 * Print a data
	 * @param data $data
	 */
	public function write($data) {
		$this->os->write($data);
	}
	
	/**
	 * Print a data and then terminate the line. 
	 * @param data $data
	 */
	public function writeln($data) {
		$this->write($data."\n");
	}
}