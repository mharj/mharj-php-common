<?php
namespace com;

class LdapException extends \Exception {
	public function __construct($message,$code=0,$file="",$line=null,$previous=null) {
		parent::__construct($message, $code, $previous);
		$this->file = $file;
		$this->line = $line;
	}
}