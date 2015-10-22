<?php
namespace lang;
use io\PrintStream;
use io\StdOutputStream;

class System extends Object {
	public static $out = null; 
	public static function __callStatic($name, $arguments) {
		if ( self::$out == null ) {
			self::$out = new PrintStream(new StdOutputStream());
		}
	}
}
// load statics
System::__callStatic(null,null);