<?php
namespace com;

class LdapBindException extends LdapException {
	public function __construct($message,$code=0,$file="",$line=null,$previous=null) {
		parent::__construct($message,$code,$file,$line,$previous);
		$this->file = $file;
		$this->line = $line;
	}
}