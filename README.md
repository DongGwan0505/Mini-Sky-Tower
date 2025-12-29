# 🏙️ Mini SKY TOWER  
### Embedded System Based Mini Urban Control Tower

> **FSM & Interrupt 중심의 센서 기반 엘리베이터 제어 임베디드 시스템**

---

## 📌 Overview

**Mini SKY TOWER**는 엘리베이터의 위치와 상태를  
센서와 **FSM(Finite State Machine)** 기반으로 제어하고,  
이를 **7-Segment 및 LCD 디스플레이로 시각화**한 임베디드 프로젝트입니다.

단순한 기능 구현이 아닌,  
**상태 정의 / 이벤트 기반 제어 / 센서 오차 보정**에 중점을 두었습니다.

---

## 🎯 Project Motivation

- 엘리베이터의 실제 위치 및 동작 상태를 직관적으로 파악하기 어려움
- 단순 모형은 센서 기반 피드백 및 상태 제어 구조가 없음
- **FSM + Interrupt 설계 경험**을 목표로 프로젝트 기획

---

## ⚙️ System Architecture

### 🔩 Hardware Components

| Component | Description |
|----------|-------------|
| MCU | STM32F411 |
| Actuator | Step Motor |
| Sensor | SR04 Ultrasonic Sensor |
| Sensor | Photo Interrupter ×3 |
| Display | 7-Segment ×4, LCD |
| Input | Button ×3 |
| Output | Buzzer |

---

### 🧠 Software Structure

```text
Application Layer
 └─ Elevator FSM
     ├─ Target Floor Control
     ├─ State Transition
     └─ Interrupt Handling

Driver Layer
 ├─ Button Driver
 ├─ FND Driver
 ├─ LCD Driver (I2C)
 ├─ SR04 Driver
 ├─ Photo Interrupt Driver
 └─ Buzzer Driver
```

### 🔁 Elevator FSM Design
FSM States
IDLE

MOVING_UP

MOVING_DOWN

STOP

State Transition Logic
text
코드 복사
IDLE  → MOVING_UP / MOVING_DOWN : Button Input
MOVING → STOP                   : Photo Interrupt
STOP → IDLE                     : Target Floor Reached
🔍 Key Point
위치 상태와 이동 상태를 분리하여 FSM 안정성 확보

📐 Sensor Fusion Strategy
Sensor	Role
SR04	연속적인 높이 값 제공
Photo Interrupter	층 도착을 보장하는 기준 이벤트

SR04 단독 사용 시 발생하는 노이즈 문제를
Photo Interrupt 기반 FSM 전이로 보정

🎬 Final Demo
📟 7-Segment: 높이 실시간 표시

🖥 LCD: 층 정보 & 상태 표시 (RUN, STOP)

🎛 Button: 목표 층 선택

🔔 Buzzer: 층 도착 알림

⚡ Photo Interrupt: 층 도착 시 인터럽트 발생

🛠️ Trouble Shooting
❌ Issue 1 – FSM 설계 문제
문제: 1F / 2F / 3F 상태만으로 FSM 구성 → 오동작

원인: 이동 과정 상태 미정의

해결: MOVING_UP / MOVING_DOWN 상태 추가

❌ Issue 2 – 전원 재시작 시 위치 불일치
문제: 시작 상태는 1F, 실제 위치는 3F

해결: 초기화 시 1F 복귀 루틴 추가

🧠 What I Learned
FSM 설계에서 과정 상태의 중요성

Interrupt는 상태 전이를 보장하는 핵심 이벤트

센서 값과 이벤트 신호의 역할 분리

임베디드 문제는 기능보다 구조에서 원인을 찾아야 함

🔧 Development Environment
MCU: STM32F411

IDE: STM32CubeIDE

Language: C

Framework: STM32 HAL

