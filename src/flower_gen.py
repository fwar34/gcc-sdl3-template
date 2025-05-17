import pygame
import math
import os
from PIL import Image

# 初始化 Pygame
pygame.init()

# 动画参数
WIDTH, HEIGHT = 800, 600  # 画面尺寸
FPS = 30                  # 帧率
DURATION = 8              # 动画时长（秒）
TOTAL_FRAMES = FPS * DURATION  # 总帧数
OUTPUT_DIR = "flower_frames"    # 输出目录
PETAL_COUNT = 12          # 花瓣数量
PETAL_LENGTH = 200        # 花瓣长度

# 颜色定义（从花蕾到开放的渐变）
START_COLOR = (150, 50, 100)   # 深红色（花蕾）
END_COLOR = (255, 150, 200)    # 浅粉色（开放）
BACKGROUND_COLOR = (230, 240, 200)  # 绿色背景
CENTER_COLOR = (255, 200, 50)   # 花蕊颜色

# 创建输出目录
os.makedirs(OUTPUT_DIR, exist_ok=True)

# 创建虚拟窗口（仅用于渲染，不显示）
screen = pygame.Surface((WIDTH, HEIGHT))

# 计算花瓣位置的函数
def get_petal_points(angle, progress):
    # 中心点坐标
    center_x, center_y = WIDTH // 2, HEIGHT // 2

    # 花瓣展开进度（0到1）
    actual_progress = max(0, progress - 0.2) / 0.8  # 前20%帧为花蕾状态

    # 花瓣内半径（随进度变化）
    inner_radius = 50 - 50 * actual_progress
    outer_radius = inner_radius + PETAL_LENGTH * actual_progress

    # 计算花瓣顶点坐标
    angle_rad = math.radians(angle)
    x1 = center_x + inner_radius * math.cos(angle_rad)
    y1 = center_y + inner_radius * math.sin(angle_rad)
    x2 = center_x + outer_radius * math.cos(angle_rad + 30)
    y2 = center_y + outer_radius * math.sin(angle_rad + 30)
    x3 = center_x + outer_radius * math.cos(angle_rad - 30)
    y3 = center_y + outer_radius * math.sin(angle_rad - 30)

    return [(x1, y1), (x2, y2), (x3, y3)]

# 生成动画帧
def generate_frames():
    for frame in range(TOTAL_FRAMES):
        # 清空背景
        screen.fill(BACKGROUND_COLOR)

        # 计算当前进度（0.0到1.0）
        progress = frame / (TOTAL_FRAMES - 1)

        # 绘制花瓣
        for i in range(PETAL_COUNT):
            angle = 360 * i / PETAL_COUNT + progress * 360  # 动态旋转效果
            points = get_petal_points(angle, progress)

            # 颜色渐变
            r = int(START_COLOR[0] + (END_COLOR[0] - START_COLOR[0]) * progress)
            g = int(START_COLOR[1] + (END_COLOR[1] - START_COLOR[1]) * progress)
            b = int(START_COLOR[2] + (END_COLOR[2] - START_COLOR[2]) * progress)
            petal_color = (r, g, b, 255)  # 添加透明度

            # 绘制单个花瓣
            pygame.draw.polygon(screen, petal_color, points)

        # 绘制花蕊
        if progress > 0.3:
            center_radius = 50 - 30 * (1 - progress)
            pygame.draw.circle(screen, CENTER_COLOR, (WIDTH//2, HEIGHT//2), int(center_radius))

        # 保存当前帧为JPG
        img = Image.frombytes("RGB", (WIDTH, HEIGHT), pygame.image.tostring(screen, "RGB"))
        frame_path = f"{OUTPUT_DIR}/A_{frame:04d}.jpg"
        img.save(frame_path, "JPEG", quality=90)

        # 显示进度
        print(f"已生成帧 {frame+1}/{TOTAL_FRAMES}")

# 执行生成
generate_frames()

# 退出Pygame
pygame.quit()
print(f"开花序列帧已生成至 {OUTPUT_DIR} 目录")
