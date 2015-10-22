<?php
namespace com;
use \DateTime;
use \DateTimeZone;

class LdapAttribute implements \ArrayAccess, \Countable, \JsonSerializable {
	private static $intAttributes = array(
		'uidnumber',
		'gidnumber',
		'shadowflag',
		'shadowexpire',
	);
	private static $dateAttributes = array(
		'modifytimestamp',
		'createtimestamp',
	);
	
	private $name;
	private $values = array();
	private $change = false;
	/**
	 * Ldap Attribute constructor
	 * @param string $name
	 * @param array $values
	 */
	public function __construct($name,array $values) {
		$this->name = $name;
		foreach ( self::fixAttributeTypes($name,$values) AS $value ) {
			$this->values[]=$value;
		}
		$this->change = false;
	}
	/**
	 * Fix Attribute types for PHP
	 * @param string $key
	 * @param array $values
	 * @return array
	 */
	private static function fixAttributeTypes($key,array $values) {
		if ( in_array($key,self::$intAttributes) ) {
			foreach ( $values AS $k => $v ) {
				$values[$k]=intVal($v);
			}
		} else if ( in_array($key,self::$dateAttributes) ) {
			foreach ( $values AS $k => $v ) {
				$values[$k] = DateTime::createFromFormat('YmdGis',rtrim($v, "Z"),new DateTimeZone('UTC'));
			}
		}
		return $values;
	}
	
	/**
	 * Get Attribute name
	 * @return string
	 */
	public function getName() {
		return $this->name;
	}
	
	/**
	 * get first value
	 * @return value
	 */
	public function first() {
		return $this->offsetGet(0);
	}
	
	/**
	 * get all values
	 * @return array
	 */
	public function getValues() {
		return $this->values;
	}
	/**
	 * Is attribute modified after constructor load
	 * @return boolean
	 */
	public function isModified() {
		return $this->change;
	}
	
	/**
	 * Check if offset exists
	 * @param offset $offset
	 * @return value
	 * @see \ArrayAccess::offsetExists
	 */
	public function offsetExists($offset) {
		return isset($this->values[$offset]);
	}

	/**
	 * Read value
	 * @param offset $offset
	 * @return value
	 * @see \ArrayAccess::offsetGet
	 */
	public function offsetGet($offset) {
		return $this->values[$offset];
	}
	
	/**
	 * Write value
	 * @param offset $offset
	 * @param value $value
	 * @see \ArrayAccess::offsetSet
	 */
	public function offsetSet($offset, $value) {
		$this->change = true;
		$this->values[$offset] = $value;
	}
	/**
	 * Clear value
	 * @param offset $offset
	 * @see \ArrayAccess::offsetUnset
	 */
	public function offsetUnset($offset) {
		unset($this->values[$offset]);
	}
	
	/**
	 * Count values in attribute
	 * @return int
	 * @see \Countable::count
	 */
	public function count() {
		return count($this->values);
	}
	
	/**
	 * Build JSON data format
	 * @return json
	 * @see \JsonSerializable::jsonSerialize
	 */
	public function jsonSerialize() {
		$data = $this->values;
		// convert date object to javascript timestamp
		if ( in_array($this->name,self::$dateAttributes) ) {
			foreach ( $data AS $k => $v ) {
				$data[$k]=($v->getTimestamp()*1000);
			}
		}
		return $data;
	}

}