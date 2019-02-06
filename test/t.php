<?php

function Encoding(){
    $fenc = new PHPFenc();
    $fenc->setSource("/home/ho80/다운로드/a_h_e152.mp4");
    $fenc->setTarget("out.mp4");
    $fenc->setPreset("SD");
    echo($fenc->getSource());
    echo($fenc->getProgress());
    echo("StartEncode");
    $fenc->StartEncode();
//    echo("Wait");
//    $fenc->Wait();
    echo("OK");
}

function Thumbnail(){
    $fenc = new PHPFenc();
    $fenc->setSource("/home/ho80/다운로드/a_h_e152.mp4");
    $fenc->setTarget("out.jpg");
    $fenc->setThumbnailTime(1);
    echo("StartThumbnail");
    $fenc->StartThumbnail();
//    echo("Wait");
//    $fenc->Wait();
    echo("OK");
}

function ThumbnailEncoding(){
    $fenc = new PHPFenc();
    $fenc->setSource("/home/ho80/다운로드/a_h_e152.mp4");
    $fenc->setTarget("out.jpg");
    $fenc->setThumbnailTime(2);
    echo("StartThumbnail");
    $fenc->StartThumbnail();
//    echo("Wait");
//    $fenc->Wait();
    echo("OK");
    sleep(1);
    $fenc->setTarget("out.mp4");
    $fenc->setPreset("SD");
    $fenc->StartEncode();
    echo("OK");
}

print("hello world!");
//Encoding();
//Thumbnail();
ThumbnailEncoding();
?>
