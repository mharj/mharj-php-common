<?php
namespace io;
use lang\Object;

abstract class OutputStream extends Object {
	public abstract function write($data);
	public function flush(){}
	public function close(){}
}