<?php
namespace com;

use lang\Object;

class LdapSearch extends Object {
	private $base;
	private $filter;
	private $attr;
	private $sort;
	
	public function __construct($base,$filter,$attr=array("*"),$sort=null) {
		$this->base = $base;
		$this->filter = $filter;
		$this->attr = $attr;
		$this->sort = $sort;
		if ( ! in_array("modifytimestamp",$this->attr) ) {
			$this->attr[]="modifytimestamp";
		}
	}
	
	public function toString() {
		return json_encode($this);
	}
	
	public function getBase() {
		return $this->base;
	}
	
	public function getFilter() {
		return $this->filter;
	}
	
	public function getAttributes() {
		return $this->attr;
	}	
}
