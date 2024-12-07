# ZephyrSkeleton

## 1. 機能概要
公式の手順を簡略・軽量化して、手軽に開発を始められる環境を目的としています。
* 開発の際はターゲットが決まっていることが多く、データ削減やCIの短縮化などを想定した環境を用意
* バージョンやリビジョンを固定して足並みをそろえた開発が必要で、その固定させた環境を用意
* コマンドプロンプトと bash 両方で使えるようにしておき、VSCode によるデバッグ環境も用意

## 2. 使い方
### 2.1. 事前準備
開発に必要なツール群のインストールを行う。

---
#### 2.1.1. Windows 向け
1. chocolatery のインストール ([公式参照](https://chocolatey.org/install))
2. 管理者権限でコマンドプロンプトを開き、下記実行により必要なツールをインストール
```
choco feature enable -n allowGlobalConfirmation
choco install cmake --installargs 'ADD_CMAKE_TO_PATH=System'
choco install ninja gperf python311 git dtc-msys2 wget 7zip
```
---
#### 2.1.2. Ubuntu 向け
パッケージリストの追加と更新
```
wget https://apt.kitware.com/kitware-archive.sh
sudo bash kitware-archive.sh
```
必要なツールのインストール
```
sudo apt install --no-install-recommends git cmake ninja-build gperf \
  ccache dfu-util device-tree-compiler wget \
  python3-dev python3-pip python3-setuptools python3-tk python3-wheel xz-utils file \
  make gcc gcc-multilib g++-multilib libsdl2-dev libmagic1
```
---

うまく行かなかった場合は、下記公式ページを参照<br>
[Getting Started Guide: Install dependencies](https://docs.zephyrproject.org/4.0.0/develop/getting_started/index.html#install-dependencies)

### 2.2.リポジトリのクローン
1. 作業用のディレクトリ zephyrproject を用意し、その中にこのリポジトリをクローン (zephyrproject と skeleton は適宜変更してOK)
```
mkdir zephyrproject
cd zephyrproject
git clone https://github.com/Corgeek/ZephyrSkeleton.git skeleton
```

### 2.3. このリポジトリ用の python 環境を構築
1. pyenv によりこのプロジェクト用の python 環境を作成
---
#### 2.3.1. Windows 向け
```
python -m venv .venv
.venv\Scripts\activate
pip install west
```
---
#### 2.3.2. Ubuntu 向け
```
python3 -m venv .venv
source .venv/bin/activate
pip install west
```
---

### 2.4. このリポジトリ用の Zephyr 環境を構築
1. west.yml の設定をもとに、このプロジェクト専用の環境を構築
```
west init -l skeleton
west update
pip install -r zephyr-env\zephyr\scripts\requirements.txt
```

### 2.5. SDK のダウンロードと設定
1. Zephyr v4.0.0 から下記コマンドで SDK をインストールできるようになった
```
cd zephyr
west sdk install
```

### 2.6. west コマンドの簡略用スクリプトを準備
---
#### 2.6.1. Windows 向け

skeleton\scripts\setup.bat をエディタで開き、下記ターゲットの設定を適宜変更＆保存して実行
> set BOARD_TYPE=bbc_microbit_v2
```
scripts\setup.bat
```
---
#### 2.6.2. Ubuntu 向け
skeleton\scripts\setup.sh をエディタで開き、下記ターゲットの設定を適宜変更＆保存して実行
> BOARD_TYPE=bbc_microbit_v2
```
./scripts/setup.sh
```
---

問題がなければ、.vscode 用の設定と scripts 以下に west_env.bat, build.bat, debug.bat が生成されています。

以上で、初回の構築は完了です。

### 2.7. 最終的なディレクトリ構成

ディレクトリ構成は以下のようになっており、SDK 以外はすべてこの中に内包しています。
```
.
└── zephyrproject/
    ├── .venv/
    ├── .west/
    ├── modules/
    ├── skeleton/
    │   ├── .vscode/
    │   ├── boards/
    │   ├── CMakeLists.txt
    │   ├── drivers/
    │   ├── include/
    │   ├── main.c
    │   ├── prj.conf
    │   ├── scripts/
    │   ├── utils/
    │   └── west.yml
    └── zephyr/
```

3. ## 開発フロー
### 3.1. VS Code による開発
1. VS Code で zephyrproject、もしくは skeleton ディレクトリを開く
2. Ctrl + Shift + B で、「Rebuild」もしくは「Build」を選びビルドを実施
3. 正常にビルドが完了したら Ctrl + Shift + B で出てくる「Flash」を選択し、実機に書き込む
4. gdb デバッガを用いたデバッグを行う場合は、Ctrl + Shift + B で出てくる「Debug」を選び gdbserver で待機状態に入る。その状態のまま F5 を押すことでアタッチ

### 3.2. コマンドによる開発
1. skeleton に移動しそれぞれ以下のコマンドを実行

| 機能 | コマンド |
|-----|----|
| Rebuild | ./scripts/build /r |
| Build | ./scripts/build.bat |
| Flash | ./scripts/build.bat /f |
| Debug | ./scripts/debug.bat |

Debug 時は、port 3333 で待機しているので sdk 内にある gdb を用いてアタッチ

