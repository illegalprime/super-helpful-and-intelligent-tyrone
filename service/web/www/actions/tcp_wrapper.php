#!/bin/php
<?php
if (!array_key_exists("comm", $_GET)) {
	echo "ERR>" . GET2String();
	return;
}

$client = stream_socket_client("tcp://127.0.0.1:8489", $errno, $errmsg);

if ($client === false) {
	echo "ERR>" . GET2String();
	return;
}

fwrite($client, $_GET["comm"] . "\n");
echo nl2br(stream_get_contents($client)) . ">" . GET2String();

fclose($client);

function GET2String() {
	$out = "?";

	foreach($_GET as $x=>$x_value) {
		$out = $out . $x . "=" . $x_value . "&";
	}
	return $out;
}
?>