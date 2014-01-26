<?php
    $base=$_REQUEST['image'];
     if(empty($base))
    {
        echo 'No data';
    }
    else
    {
    $binary=base64_decode($base);
    
     function generate_chars()
    {
        $num_chars = 4; //max length of random chars
        $i = 0;
        $my_keys = "123456789abcdefghijklmnopqrstuvwxyz"; //keys to be chosen from
        $keys_length = strlen($my_keys);
        $url  = "";
        while($i<$num_chars)
        {
            $rand_num = mt_rand(1, $keys_length-1);
            $url .= $my_keys[$rand_num];
            $i++;
        }
        return $url;
    }
     $chars = generate_chars();
     while( file_exists("photos/".$chars.".jpg") )
     {
            $chars = generate_chars();
     }
    $test="photos/".$chars.".jpg";
    $file = fopen($test, 'wb');
    fwrite($file, $binary);
    fclose($file);
    echo 'success';
    exec("python runocr.py ".$test);
}
?>