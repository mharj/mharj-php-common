<?php
namespace lang;

class Object {
	public function hashCode() {
		return spl_object_hash($this);
	}
	public function toString() {
		return get_class($this)."@".$this->hashCode($this);
	}
}