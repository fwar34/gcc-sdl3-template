# 生成小球移动动画
import pygame
from PIL import Image
import os

# 初始化 Pygame
pygame.init()

# 动画参数配置
WIDTH, HEIGHT = 800, 600  # 窗口尺寸
BACKGROUND_COLOR = (30, 30, 30)  # 背景色（深灰）
BALL_COLOR = (255, 100, 100)    # 小球颜色（红）
BALL_RADIUS = 50               # 小球半径
FPS = 30                       # 帧率（每秒帧数）
DURATION = 2                   # 动画时长（秒）
OUTPUT_FOLDER = "animation_frames"  # 输出文件夹

# 计算总帧数
TOTAL_FRAMES = int(FPS * DURATION)

# 创建窗口和时钟
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

# 初始化小球位置（从左到右移动）
ball_x = 0
ball_y = HEIGHT // 2
speed = WIDTH / TOTAL_FRAMES  # 每帧移动速度

# 创建输出文件夹（若不存在）
os.makedirs(OUTPUT_FOLDER, exist_ok=True)

# 生成动画帧
for frame in range(TOTAL_FRAMES):
    # 处理退出事件
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()
    
    # 更新小球位置
    ball_x += speed
    if ball_x > WIDTH + BALL_RADIUS:
        ball_x = -BALL_RADIUS  # 循环移动（可选）
    
    # 绘制帧内容
    screen.fill(BACKGROUND_COLOR)  # 清空背景
    pygame.draw.circle(screen, BALL_COLOR, (int(ball_x), int(ball_y)), BALL_RADIUS)  # 绘制小球
    
    # 将 Pygame 表面转换为 PIL 图像并保存为 JPG
    surface = pygame.surfarray.array3d(screen)
    img = Image.fromarray(surface)
    frame_path = os.path.join(OUTPUT_FOLDER, f"A_{frame:04d}.jpg")
    img.save(frame_path, "JPEG", quality=90)  # quality 控制画质（1-100）
    
    # 控制帧率
    clock.tick(FPS)
    print(f"已保存第 {frame+1}/{TOTAL_FRAMES} 帧")

# 退出 Pygame
pygame.quit()
print("动画帧生成完成！")