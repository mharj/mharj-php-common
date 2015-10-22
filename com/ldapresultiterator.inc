<?php
namespace com;

class LdapResultIterator implements \Iterator {
	private $sr;
	private $softException;
	private $entry = null;
	public function __construct(LdapResult $sr,$softException = null) {
		$this->sr = $sr;
		$this->softException = $softException;
	}
	
	public function current() {
		if ( $this->entry == null ) { // if using directly rewind
			$this->rewind();
		}
		$entry = new LdapEntry( $this->sr->getKey($this->entry) );
		if ( ($data = $this->sr->getCurrent($this->entry)) !== false  ) {
			unset($data['count']);
			foreach ( $data AS $k => $v ) {
				if ( ! is_array($v) )  {
					unset($data[$k]);
				} else {
					unset($data[$k]['count']);
				}
			}
			foreach ( $data AS $k => $v ) {
				$entry->setAttribute(new LdapAttribute(strtolower($k),$v));
			}
		}
		return $entry;
	}

	public function key() {
		return $this->sr->getKey($this->entry);
	}

	public function next() {
		$this->entry = $this->sr->getNextEntry($this->entry);
	}

	public function rewind() {
		$this->entry = $this->sr->getFirstEntry();
	}

	public function valid() {
		return ( $this->entry != null );
	}

}