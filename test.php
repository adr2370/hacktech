<?php
exec("python runocr.py photos/fadx.jpg", $out);
print_r($out);
?>