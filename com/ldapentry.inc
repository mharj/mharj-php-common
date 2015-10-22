<?php
namespace com;

class LdapEntry implements \JsonSerializable {
	private static $notModifiableAttributes = array(
		'modifytimestamp',
		'createtimestamp',
		'creatorsname',
		'modifiersname',
	);
	private $dn;
	private $attributes = array();
	
	/**
	 * Ldap Entry constuctor
	 * @param string $dn entry distinguished name
	 */
	public function __construct($dn) {
		$this->dn = $dn;
	}
	
	/**
	 * Get Entry distinguished name
	 * @return string
	 */
	public function getDn() {
		return $this->dn;
	}
	/**
	 * Save LdapAttribute to Entry
	 * @param \com\LdapAttribute $attr
	 */
	public function setAttribute(LdapAttribute $attr) {
		$this->attributes[$attr->getName()]=$attr;
	}
	/**
	 * Get LdapAttribute with attribute name
	 * @param string $name
	 * @return LdapAttribute
	 */
	public function getAttribute($name) {
		return $this->attributes[strtolower($name)];
	}
	
	/**
	 * Get LdapAttribute with attribute name
	 * @param string $name
	 * @return LdapAttribute
	 * @see LdapEntry\setAttribute
	 */
	public function __get($name) {
		return $this->getAttribute($name);
	}
	/**
	 * Check if attribute exists
	 * @param string $name
	 * @return boolean
	 */
	public function __isset($name) {
		return isset($this->attributes[$name]);
	}
	
	/**
	 * Get changed Entry data for LDAP modify
	 * @return array
	 */
	public function getUpdateData() {
		$out = array();
		foreach ($this->attributes AS $attr ) {
			if ( $attr->isModified() && ! in_array( $attr->getName() , self::$notModifiableAttributes ) ) {
				$out[$attr->getName()]=$attr->getValues();
			}
		}
		return $out;
	}
	
	/**
	 * Return attribute names as array
	 * @return array
	 */
	public function getAttributeNames() {
		return array_keys($this->attributes);
	}
	
	/**
	 * jsonSerialize implementation
	 * @return json
	 */
	public function jsonSerialize() {
		return array($this->dn=>$this->attributes);
	}
}
