<?php
namespace io;

class ArrayOutputStream extends OutputStream implements \ArrayAccess {
	private $data=array();
	
	public function write($data) {
		$this->data[]=$data;
	}
	
	public function toString() {
		return implode("\n",$this->data);
	}

	public function offsetExists($offset) {
		return (isset($this->data[$offset]));
	}

	public function offsetGet($offset) {
		return $this->data[$offset];
	}

	public function offsetSet($offset, $value) {
		return $this->data[$offset]=$value;
	}

	public function offsetUnset($offset) {
		unset($this->data[$offset]);
	}
	
}