# Mini-Sky-Tower
STM32CubeIDE 프로그램과 f411re 보드, StepMotor, LCD, 7-segment, button, SR04, Buzzer를 활용한 미니 스카이타워 제작 프로젝트

🏙️ Mini SKY TOWER

Embedded System Based Mini Urban Control Tower

센서 기반 엘리베이터 제어를 통해
FSM 설계와 Interrupt 중심 임베디드 시스템 구조를 구현한 프로젝트

📌 Overview

Mini SKY TOWER는 엘리베이터의 위치와 상태를
센서와 FSM(Finite State Machine)을 기반으로 제어하고,
이를 7-Segment 및 LCD 디스플레이로 시각화한 임베디드 시스템 프로젝트입니다.

본 프로젝트는 단순한 기능 구현을 넘어,
상태 정의, 이벤트 기반 제어, 센서 오차 보정, 트러블 슈팅 경험에 초점을 두었습니다.

🎯 Project Motivation

엘리베이터의 실제 위치 및 동작 상태는 내부에서 직관적으로 파악하기 어려움

단순 모형은 센서 기반 피드백 및 상태 제어 구조가 부재

임베디드 시스템 관점에서 FSM과 Interrupt 설계의 중요성을 실습하고자 기획

⚙️ System Architecture
Hardware Components
Component	Description
MCU	STM32F411
Actuator	Step Motor (엘리베이터 상승/하강)
Sensor	SR04 Ultrasonic Sensor (높이 측정)
Sensor	Photo Interrupter ×3 (층 도착 검출)
Display	7-Segment ×4 (높이 표시), LCD (층/상태 표시)
Input	Button ×3 (목표 층 선택)
Output	Buzzer (층 도착 알림)
Software Structure
Application Layer
 └─ Elevator FSM
     ├─ Target Floor Management
     ├─ State Transition Control
     └─ Interrupt Handling

Driver Layer
 ├─ Button Driver
 ├─ FND (7-Segment) Driver
 ├─ LCD Driver (I2C)
 ├─ SR04 Driver
 ├─ Photo Interrupt Driver
 └─ Buzzer Driver

HAL Layer
 └─ STM32 HAL

🔁 Elevator FSM Design
FSM States

IDLE

MOVING_UP

MOVING_DOWN

STOP

Key Design Concept

**위치 상태(1F/2F/3F)**와 **이동 과정 상태(Moving)**를 분리

버튼 입력은 Target_F로만 반영

Photo Interrupt 발생 시 FSM 상태 전이를 확정

IDLE → MOVING_UP / MOVING_DOWN : Button Input
MOVING → STOP                  : Photo Interrupt 발생
STOP → IDLE                    : 목표 층 도달

📐 Sensor Fusion Strategy
Sensor	Role
SR04	연속적인 높이 값 제공
Photo Interrupter	층 도착을 보장하는 기준 이벤트

SR04 단독 사용 시 노이즈 및 오차로 인해
층 도착 판단이 불안정하여,
Photo Interrupter를 기준 이벤트로 활용하여 FSM 전이를 안정화함

🎬 Final Demo

7-Segment: 엘리베이터 높이 실시간 표시

LCD: 층 정보 및 상태 (RUN, STOP) 출력

Button: 목표 층 선택

Buzzer: 층 도착 알림

Photo Interrupt: 층 도착 시 외부 인터럽트 발생

🛠️ Trouble Shooting
Issue 1 – FSM 설계 문제

문제

초기 FSM을 1F / 2F / 3F 상태만으로 구성

버튼 입력과 인터럽트가 동시에 발생 시 오동작

원인

위치 상태와 이동 상태를 동일한 FSM 상태로 취급

해결

MOVING_UP / MOVING_DOWN 상태 추가

버튼 입력은 Target_F로만 관리

Issue 2 – 전원 재시작 시 위치 불일치

문제

시작 상태는 1F지만, 실제 엘리베이터 위치는 3F

해결

Elevator_init()에서 강제로 1F로 복귀하는 초기화 루틴 추가

🧠 What I Learned

FSM 설계 시 결과 상태보다 과정 상태가 중요

Interrupt는 단순한 신호가 아닌 상태 전이를 보장하는 핵심 이벤트

센서는 값을 제공하고, FSM은 구조를 제공한다

임베디드 시스템 문제는 기능보다 구조에서 원인을 찾아야 함

🔧 Development Environment

MCU: STM32F411

IDE: STM32CubeIDE

Language: C

Framework: STM32 HAL

👤 Author

이동관

Embedded / Digital System Engineer

GitHub: DongGwan0505

⭐ Future Improvements (Optional)

층 수 확장 (N층 구조)

비상 정지 상태 추가

UART 기반 상태 로그 출력

센서 캘리브레이션 알고리즘 적용
