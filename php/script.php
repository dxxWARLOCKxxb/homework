#!/usr/bin/php
<?php
$URL = 'http://kernel.ubuntu.com/~kernel-ppa/mainline/';
$page = @file_get_contents($URL);
preg_match_all('#href="(v[\d\.]+/)"#', $page, $last_version);
$last_version = $last_version[1];
natsort($last_version);
$last_version = array("name" => $last_version[count($last_version) - 2], "url" => $URL . $last_version[count($last_version) - 2]);
echo "Найденная последняя версия ядра linux: {$last_version['name']}\n";
$page = @file_get_contents($last_version['url']);
preg_match_all('#href="(\w+\-\w+\-[\d\.\-]+[_|g]+.*_a[lmd64]+\.deb)"#', $page, $links);
$links = $links[1];
$links = array_unique($links);
foreach ($links as $link) {
    echo "Загружаю $link\n";
    @file_put_contents($link, @file_get_contents($last_version['url'].$link));
}
echo "Запускаю обновление:\n";
exec('sudo dpkg -i *.deb');
foreach ($links as $link) {
    echo "Удаляю $link\n";
    unlink($link);
}
?>

