#!/bin/bash
set -e

BUILD_DIR=/root/voidterminal/build/linux/x64/release/bundle
DEB_ROOT=/root/deb-build
APP_DIR="$DEB_ROOT/usr/lib/void-terminal"

# 清理并创建目录结构
rm -rf "$DEB_ROOT"
mkdir -p "$DEB_ROOT/DEBIAN"
mkdir -p "$APP_DIR"
mkdir -p "$DEB_ROOT/usr/bin"
mkdir -p "$DEB_ROOT/usr/share/applications"
mkdir -p "$DEB_ROOT/usr/share/icons/hicolor/256x256/apps"

# 复制构建产物
cp -r "$BUILD_DIR"/* "$APP_DIR/"

# 可执行文件软链接
ln -s ../lib/void-terminal/void_terminal_linux "$DEB_ROOT/usr/bin/void-terminal"

# 生成一个简单的图标（256x256 纯色 PNG）
python3 - <<'PYEOF'
import zlib, struct
w = h = 256
# 深色背景 + 中心浅色圆点
rows = []
for y in range(h):
    row = bytearray()
    row.append(0)  # filter none
    for x in range(w):
        dx = x - w/2
        dy = y - h/2
        d = (dx*dx + dy*dy) ** 0.5
        if d < 80:
            r, g, b = 79, 140, 255   # vtAccent
        elif d < 120:
            r, g, b = 23, 26, 35     # vtCard
        else:
            r, g, b = 15, 17, 23     # vtBg
        row.extend([r, g, b])
    rows.append(bytes(row))
raw = b''.join(rows)
def chunk(tag, data):
    c = tag + data
    return struct.pack('>I', len(data)) + c + struct.pack('>I', zlib.crc32(c))
ihdr = struct.pack('>IIBBBBB', w, h, 8, 2, 0, 0, 0)
png = b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', ihdr) + chunk(b'IDAT', zlib.compress(raw)) + chunk(b'IEND', b'')
open('/root/deb-build/usr/share/icons/hicolor/256x256/apps/void-terminal.png', 'wb').write(png)
print('图标已生成')
PYEOF

# control 文件
cat > "$DEB_ROOT/DEBIAN/control" <<'EOF'
Package: void-terminal
Version: 1.0.0
Section: net
Priority: optional
Architecture: amd64
Depends: libgtk-3-0, libglib2.0-0, libc6
Maintainer: VoidTerminal <voidterminal@example.com>
Homepage: https://buer.kdns.fr
Description: 虚空终端 Linux 桌面版
 虚空终端（buer.kdns.fr）的 Linux 原生桌面客户端，基于 Flutter 构建。
 支持全局大厅、私聊、群聊、好友管理、朋友圈等功能。
EOF

# .desktop 文件
cat > "$DEB_ROOT/usr/share/applications/void-terminal.desktop" <<'EOF'
[Desktop Entry]
Name=虚空终端
Comment=虚空终端聊天客户端
Exec=/usr/bin/void-terminal
Icon=void-terminal
Type=Application
Categories=Network;Chat;InstantMessaging;
Terminal=false
StartupWMClass=void_terminal_linux
EOF

# 打包
dpkg-deb --build "$DEB_ROOT" /root/void-terminal_1.0.0_amd64.deb

echo "=== 打包完成 ==="
ls -lh /root/void-terminal_1.0.0_amd64.deb
dpkg-deb --info /root/void-terminal_1.0.0_amd64.deb | head -20
