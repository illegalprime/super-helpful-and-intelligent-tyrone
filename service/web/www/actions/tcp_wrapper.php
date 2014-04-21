#!/bin/php
<?php
if (!array_key_exists("comm", $_GET)) {
	echo "ERR>" . GET2String();
	return;
}

$client = stream_socket_client("tcp://127.0.0.1:13", $errno, $errmsg); # 8489	

if ($client === false) {
	echo "ERR>" . GET2String();
	return;
}

fwrite($client, $_GET["comm"]);
echo stream_get_contents($client) . ">" . GET2String();

fclose($client);

function GET2String() {
	$out = "?";

	foreach($_GET as $x=>$x_value) {
		$out = $out . $x . "=" . $x_value . "&";
	}
	return $out;
}
?>