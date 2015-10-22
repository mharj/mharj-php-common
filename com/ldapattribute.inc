<?php
namespace com;

class LdapAttribute implements \ArrayAccess, \Countable {
	private $name;
	private $values = array();
	private $change = false;
	
	public function __construct($name,$values) {
		$this->name = $name;
		foreach ( $values AS $value ) {
			$this->values[]=$value;
		}
		$this->change = false;
	}
	
	public function getName() {
		return $this->name;
	}
	

	public function first() {
		return $this[0];
	}
	
	public function getValues() {
		return $this->values;
	}
	
	public function isModified() {
		return $this->change;
	}
	
	// ArrayAccess
	public function offsetExists($offset) {
		return isset($this->values[$offset]);
	}

	public function offsetGet($offset) {
		return $this->values[$offset];
	}

	public function offsetSet($offset, $value) {
		$this->change = true;
		$this->values[$offset] = $value;
	}

	public function offsetUnset($offset) {
		unset($this->values[$offset]);
	}
	// Countable
	public function count() {
		return count($this-values);
	}
	
}