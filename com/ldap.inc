<?php
namespace com;

class Ldap {
	private $ds = null;
	private $eh;
	
	public function __construct($server,$port=389) {
		$this->eh =  array(&$this, 'wrap');
		set_error_handler( $this->eh );
		$this->ds = ldap_connect($server,$port);
		restore_error_handler();
	}
	
	public function __destruct() {
		if ( ! $this->isClosed() ) {
			$this->close();
		}
	}
	
	public function bind($dn=null,$password=null) {
		set_error_handler($this->eh );
		ldap_bind($this->ds,$dn,$password);
		restore_error_handler();
	}
	
	public function close() {
		set_error_handler( $this->eh );
		if ( ldap_unbind($this->ds) == false ) {
			restore_error_handler();
			throw new LdapException(ldap_error($this->ds));
		}
		restore_error_handler();
		$this->ds = null;
	}
	
	public function search(LdapSearch $search) {
		set_error_handler( $this->eh );
		$sr = ldap_search($this->ds,$search->getBase(),$search->getFilter(),$search->getAttributes());
		$ldapResult = new LdapResult($this->ds,$sr);
		restore_error_handler();
		return $ldapResult;
	}
	
	public function isClosed() {
		return $this->ds==null?true:false;
	}
	
	/**
	 * Replace modified attributes
	 * @param \com\LdapEntry $entry
	 * TODO: reload data to update values in entry (modifydate)
	 */
	public function persist(LdapEntry $entry) {
		try { // modify entry
			$modifyts = new LdapSearch($entry->getDn(),"objectclass=*",array("modifytimestamp"));
			if ( $entry->modifytimestamp[0] != $this->search($modifyts)->getIterator()->current()->modifytimestamp[0] ) {
				throw new LdapException("Entry was changed already");
			}
			$this->modReplace($entry->getDn(),$entry->getUpdateData());
			// update TS from LDAP
			$entry->modifytimestamp[0] = $this->search($modifyts)->getIterator()->current()->modifytimestamp[0];
		} catch( LdapNotFoundException $ex) {
			// TODO: create entry
		}
	}
	
	/**
	 * 
	 * @param string $dn
	 * @param array $mod
	 */
	public function modReplace($dn,array $mod) {
		set_error_handler( "self::wrap" );
		ldap_mod_replace($this->ds,$dn,$mod);
		restore_error_handler();
	}
	
	public function wrap($errno, $errstr, $errfile, $errline) {
		if ( $this->ds != null ) {
			$errno = ldap_errno($this->ds);
		}
//		echo "ERROR:".$errno."\n";
		switch (ldap_errno($this->ds)) {
			case 32: 
				throw new LdapNotFoundException($errstr,$errno,$errfile,$errline);
			case 34:
			case 2:
				throw new LdapBindException($errstr,$errno,$errfile,$errline);
			default:
				throw new LdapException($errstr,$errno,$errfile,$errline);
		}		
	}
}