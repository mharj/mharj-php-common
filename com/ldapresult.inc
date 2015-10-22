<?php
namespace com;

class LdapResult implements \IteratorAggregate {
	private $ds = null;
	private $sr = null;
	private $iter = null;
	/**
	 * 
	 * @param ldap_link_resource $ds
	 * @param ldap_result_resource $sr
	 */
	public function __construct($ds,$sr) {
		$this->ds = $ds;
		$this->sr = $sr;
		$this->iter = new LdapResultIterator($this);
	}
	
	public function getIterator() {
		return $this->iter;
	}
	
	/**
	 * Get first ldap entry resource
	 * @return resource 
	 */
	public function getFirstEntry() {
		return ldap_first_entry($this->ds,$this->sr);
	}
	
	/**
	 * Get next ldap entry resource
	 * @param resource $entry
	 * @return resource
	 */
	public function getNextEntry($entry) {
		return $this->entry = ldap_next_entry($this->ds,$entry);
	}
	
	/**
	 * Get current key for iterator
	 * @param resource $entry
	 * @return string ldap dn
	 */
	public function getKey($entry) {
		return ldap_get_dn($this->ds,$entry);
	}
	
	/**
	 * 
	 * @param resource $entry
	 */
	public function getCurrent($entry) {
		return ldap_get_attributes($this->ds,$entry);
	}
}