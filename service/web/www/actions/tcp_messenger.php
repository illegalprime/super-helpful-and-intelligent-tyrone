<?php

$service_port = getservbyname('daytime', 'tcp');
$address = gethostbyname('127.0.0.1');

echo "Listening to $address on port $service_port:<br/>";



?>