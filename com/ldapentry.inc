<?php
namespace com;

class LdapEntry {
	private $dn;
	private $attributes = array();
	public function __construct($dn) {
		$this->dn = $dn;
	}
	
	public function getDn() {
		return $this->dn;
	}
	
	public function setAttribute(LdapAttribute $attr) {
		$this->attributes[$attr->getName()]=$attr;
	}
	
	public function getAttribute($name) {
		return $this->attributes[strtolower($name)];
	}
	
	public function __get($name) {
		return $this->getAttribute($name);
	}
	
	public function __isset($name) {
		return isset($this->attributes[$name]);
	}
	
	public function getUpdateData() {
		$out = array();
		foreach ($this->attributes AS $attr ) {
			if ( $attr->isModified() ) {
				$out[$attr->getName()]=$attr->getValues();
			}
		}
		return $out;
	}
	
	public function getAttributeNames() {
		return array_keys($this->attributes);
	}
}
