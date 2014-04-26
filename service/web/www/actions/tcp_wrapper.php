#!/bin/php
<?php
if (!array_key_exists("comm", $_GET)) {
	echo '1';
	echo "ERR>" . GET2String();
	return;
}

$client = stream_socket_client("tcp://127.0.0.1:8489", $errno, $errmsg);

if ($client === false) {
	echo '2';
	echo "ERR>" . GET2String();
	return;
}

fwrite($client, $_GET["comm"] . "\r\n");
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