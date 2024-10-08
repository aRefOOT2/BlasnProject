# Blasn Project公式資料集

![Blasn_Logo](https://github.com/user-attachments/assets/94b190ac-fc71-45db-9852-21c7ec78e11a)

更新日時：2024/09/05  08:40

## 目次
1. [Blasn Projectとは](#blasn-projectとは)
   - [Blasn OS/Blasn Kernelとは](#blasn-osblasn-kernelとは)
     - [Blasn OSとは](#blasn-osとは)
     - [Blasn Kernelとは](#blasn-kernelとは)
     - [Blasn Kernel Shell(BKS)とは](#blasn-kernel-shellbksとは)

2. [実行可能なコマンド](#実行可能なコマンド)
    - [version](#versionコマンド)
    - [help](#helpコマンド)
    - [dir](#dirコマンド)
    - [cd](#cdコマンド)
    - [exit](#exitコマンド)
    - [hello](#helloコマンド)

3. [ニュース](#ニュース) 

4. [開発方針](#開発方針)

5. [ソースコードのダウンロード](#ソースコードのダウンロード)

## 1. Blasn Projectとは
**Blasn OS、Blasn Kernelなどのプロジェクトの総称です。**

### 2. Blasn OS/Blasn Kernelとは
#### Blasn OSとは
**Blasn Kernel上で動作するOSです。**

　実行可能ファイルはBlasn Kernelと同じです。

#### Blasn Kernelとは
**個人で開発しているカーネルです。**

　実行可能ファイルは`Blasn eXectable Object(bxo)`です。

####  Blasn Kernel Shell(BKS)とは
**Blasn Kernel上で動作するシェルプログラムです。**

　必要最低限のコマンドを内蔵しており、Blasn OSが起動できない問題を見つけ、取り除くことを目的としたプログラムです。

　実行ファイルは、`/kernel/shell/shell.bxo`に存在します。

　Blasn Kernel Shellでは、`bxo`ファイルの他に、シェルスクリプトとして`sh`ファイルも実行可能です。

## 2. 実行可能なコマンド
**ここで紹介するコマンドはすべてBKSに内蔵されているコマンドです。**

### versionコマンド
Blasn Kernel Shellのバージョンを表示します。

### helpコマンド
Blasn Kernel Shellに内蔵されているコマンドを一覧表示します。各コマンドの簡単な説明もついています。

### dirコマンド
カレントディレクトリ内のフォルダ/ディレクトリを表示します。

### cdコマンド
カレントディレクトリを変更します。

### exitコマンド
プログラムを終了します。`sh`ファイルがサポートされた場合、シェルスクリプトを終了します。

### helloコマンド
`Hello, user!`と表示します。

## 3. ニュース
### 1.0.3 Alpha
　1.0.3 Alphaでは、追加が延長された例外処理の拡張を行う予定です。

### 1.0.2 Alpha
　1.0.1 Alphaで追加された機能によって引き起こされた重大な問題を修正しました。

## 4. 開発方針
### 資料集の整備
　新しいバージョンで何が追加されるのか等、資料を整備していきます。

### バージョン管理の徹底
　1.0.x PAの次は1.0.x A、その次は1.0.x B、その次は1.0.x MR…といったようなサイクルに従って開発していきます。

## 5. 各ステージの説明

### Pre-Alpha
　バグが多く残されており、実験的な機能が含まれる場合のあるステージです。

　各マイナーアップデートごとにフォルダが分けられ、各フォルダ内にそのマイナーバージョンの最終パッチが当てられたソースコードとビルド番号が記述されたテキストファイルが保存されています。

### Alpha
　既知のバグや未知のバグが残されているステージです。Pre-Alphaステージよりも安定しており、Pre-Alphaステージには含めなかった機能が実験的に含まれる場合があります。

　Alphaステージでは、すべてのリリースが保存されています。特定のリリースを保存する場合は、`[プログラム名]-[バージョン].zip`をダウンロードしてください。

### Beta
　Alphaステージと比べて、比較的多くのバグが修正されたステージです。未知のバグが存在する可能性もありますが、Alphaステージのリリースと比べて安定しているステージです。

　各リリースは、Alphaバージョンと同じように配布されます。

### Master Release
　ほとんどのバグが修正された正式版です。MRでマイナーアップデートが行われた場合、MRx(マイナーバージョン)と表記されます。
　
## 6. ソースコードのダウンロード

#### 各プロジェクトのソースコードは、下記リンクよりダウンロードすることができます。

Blasn Kernel :
[こちら](https://github.com/aRefOOT2/BlasnProject/tree/kernel)


Blasn Kernel Shell :
[こちら](https://github.com/aRefOOT2/BlasnProject/tree/kernel/shell)


Blasn OS :
[こちら](https://github.com/aRefOOT2/BlasnProject/tree/os)

<hr>

Blasn Project
![Blasn_Logo](https://github.com/user-attachments/assets/0af88695-ed91-46c0-876f-3eb7a6668891)
