[![Build Status][build-status-img]][travis-ci]

# staffonly -- declaration lint

外部参照を制限するためのソースコード解析ツールです。

## 背景

下位階層を使えない様にライブラリ分割しても、言語の標準ライブラリを使うのを制限できません。
使って欲しくない機能をコンパイルエラーにするために作りました。

## 使い方

### 1. 定義ファイル .staffonly にソースが在るフォルダと、エラーにするincludeを書きます。

    comm/urart
        <dirent.h>
        <sys/stat.h>

### 2. フォルダを指定してstaffonlyを起動します。

    $ staffonly Samples
    main.c 9: #include <dirent.h>
    main.c 10: #include <sys/stat.h>
    2 ERRORS.

## 対応状況

* 対応しているのはC言語のみです。
* エラーにしているのはincludeのみです。
* フォルダ毎にエラーにするincludeを指定します。

## お願い

* 他の言語にも対応して戴いたり拡張して戴けると、嬉しいです。
* コンパイラやlintに組み込んで戴けると、もっと嬉しいです。

## License

Licensed under the [MIT](LICENSE.txt) License.
