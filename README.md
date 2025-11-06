
<div id="top"></div>

<p align="center">
  <a href="https://youtu.be/mO80Yf0q98A" target="_blank">
    <img src="https://img.shields.io/badge/🎥%20YouTube%20Demo-Click%20to%20Watch-red?style=for-the-badge&logo=youtube" />
  </a>
</p>


<h1 align="center">🎨 MFC 기반 이미지 분석 & 좌표 시각화 프로그램</h1>

<p align="center">
  C++/MFC로 제작된 <b>이미지 무게중심(centroid) 계산</b>과 <b>좌표 시각화/이동</b> 데모 프로그램입니다.<br/>
  좌표를 입력하거나 랜덤으로 생성하여 원 이동을 시각화하고, BMP 이미지를 불러와 <b>검은색 픽셀의 중심</b>을 계산해 화면에 표시합니다.
</p>


<!-- ──────────────────────────────────────────────────────────────────────────────
  Table of Contents
──────────────────────────────────────────────────────────────────────────────── -->
<h3>📚 Table of Contents</h3>
<div class="toc">
  <ol>
    <li><a href="#about">프로젝트 소개</a></li>
    <li><a href="#features">주요 기능</a></li>
    <li><a href="#how-it-works">동작 원리</a></li>
    <li><a href="#ui">UI & 조작</a></li>
    <li><a href="#tech">기술 스택</a></li>
    <li><a href="#structure">폴더 구조</a></li>
    <li><a href="#build">빌드 & 실행</a></li>
    <li><a href="#roadmap">로드맵 (OpenCV 확장)</a></li>
    <li><a href="#insights">개선점 & 배운 점</a></li>
    <li><a href="#credits">크레딧</a></li>
  </ol>
</div>

<hr/>

<!-- ──────────────────────────────────────────────────────────────────────────────
  About
──────────────────────────────────────────────────────────────────────────────── -->
<h2 id="about">1) 프로젝트 소개</h2>
<blockquote>
MFC 대화상자(Dialog) 기반으로, <b>좌표 입력/랜덤 생성 → 원 시각화 및 이동 → 화면 캡처 저장</b>을 수행하며,<br/>
BMP 이미지를 불러와 <b>검은색 픽셀들의 무게중심(centroid)</b>을 계산해 화면에 표시합니다.
</blockquote>
<a class="backtotop" href="#top">⬆ Back to top</a>

<!-- ──────────────────────────────────────────────────────────────────────────────
  Features
──────────────────────────────────────────────────────────────────────────────── -->
<h2 id="features">2) 주요 기능</h2>

- 🔵 **원(원형 객체) 시각화**: 시작 좌표와 반지름으로 도형을 그립니다.
- 🎲 **랜덤 좌표 생성**: 유효 범위 내 임의 시작/목표 좌표를 생성합니다.
- 🏃 **원 이동 애니메이션**: 시작점 → 목표점으로 단계적 이동(보간) + 즉시 화면 갱신.
- 🖼 **이미지 로딩**: BMP 파일을 열어 전용 뷰에 표시합니다.
- 🎯 **무게중심(centroid) 계산**: 검은색(B=0,G=0,R=0) 픽셀을 스캔해 평균 좌표를 계산, X 마크로 시각화.
- 📸 **화면 캡처 자동 저장**: 이동 루프 중 지정 영역을 BitBlt로 가져와 타임스탬프명 BMP로 저장.

<a class="backtotop" href="#top">⬆ Back to top</a>

<!-- ──────────────────────────────────────────────────────────────────────────────
  How it Works
──────────────────────────────────────────────────────────────────────────────── -->
<h2 id="how-it-works">3) 동작 원리</h2>

<h4>✅ 이미지 무게중심(centroid)</h4>
- <code>CImage</code>의 픽셀 버퍼(BGRA, 4바이트)를 직접 접근해 <b>검은색 픽셀</b>의 좌표를 누적 평균합니다.<br/>
- 계산된 중심에 대해 <b>X 마킹</b>(양 방향 대각선)을 적용하고, 현재 좌표를 텍스트로 표기합니다.

<pre class="code"><code>// 핵심 아이디어 요약 (의사 코드)
for y in [0, h):
  for x in [0, w):
    pixel = BGRA(x, y)
    if pixel == (0,0,0):
       xsum += x; ysum += y; count++

centerX = xsum / count; centerY = ysum / count
drawXMark(centerX, centerY)
</code></pre>

<h4>✅ 원 이동 & 화면 캡처</h4>
- 시작점(StartPoint)에서 목표점(EndPoint)까지 x/y 각각을 선형 보간하며 이동합니다.
- 각 단계에서 BitBlt로 지정 영역을 메모리 DC → <code>CImage</code>로 복사 후 <b>BMP 저장</b>.

<pre class="code"><code>// 이동 루프 개념
while (!reached):
  captureWindowRectToImage();
  start.x += (end.x - start0.x) / speed;
  start.y += (end.y - start0.y) / speed;
  repaint();
  sleep(interval);
</code></pre>

<a class="backtotop" href="#top">⬆ Back to top</a>

<!-- ──────────────────────────────────────────────────────────────────────────────
  UI
──────────────────────────────────────────────────────────────────────────────── -->
<h2 id="ui">4) UI & 조작</h2>

- <b>입력 필드</b>: StartX / StartY / EndX / EndY / Radius
- <b>버튼</b>:
  - <span class="badge">Draw</span> : 반지름 무작위 설정 후 원 그리기
  - <span class="badge">Dice</span> : 유효 범위 내 랜덤 좌표 생성
  - <span class="badge">Action</span> : 시작 → 목표로 이동 + 캡처 저장 루프
  - <span class="badge">Open</span> : BMP 파일 열기 → centroid 계산 및 표시
- <b>서브 다이얼로그</b>:
  - <span class="badge">Image View</span> : BMP 미리보기 + 중심 좌표 텍스트 표시
  - <span class="badge">Parameter</span> : (확장용 자리)

<a class="backtotop" href="#top">⬆ Back to top</a>

<!-- ──────────────────────────────────────────────────────────────────────────────
  Tech Stack
──────────────────────────────────────────────────────────────────────────────── -->
<h2 id="tech">5) 기술 스택</h2>

- Language: C++17
- Framework: MFC (Dialog-based)
- Graphics: GDI(DC, BitBlt), CImage
- Build: MSVC / Visual Studio
- OS: Windows

<a class="backtotop" href="#top">⬆ Back to top</a>

<!-- ──────────────────────────────────────────────────────────────────────────────
  Structure
──────────────────────────────────────────────────────────────────────────────── -->
<h2 id="structure">6) 폴더 구조</h2>

```
MFCProject/
├─ MFCProjectDlg.h / .cpp      # 메인 대화상자: 좌표/버튼/그리기/이동/열기/캡처
├─ CDlgImage.h / .cpp          # 이미지 표시/centroid 계산/좌표 텍스트 출력
├─ CDlgParameter.h / .cpp      # (옵션) 파라미터 확장용
├─ pch.h / pch.cpp             # 공통 헤더 및 상수 (WindowsSizeX/Y 등)
├─ framework.h, resource.h     # 프레임워크/리소스 ID
├─ res/                        # 버튼 비트맵 등 리소스 (IDB_On/Off, DiceOn/Off...)
└─ MFCProject(.h/.cpp), *.sln  # 앱 엔트리 및 솔루션 파일
```

<a class="backtotop" href="#top">⬆ Back to top</a>

<!-- ──────────────────────────────────────────────────────────────────────────────
  Build
──────────────────────────────────────────────────────────────────────────────── -->
<h2 id="build">7) 빌드 & 실행</h2>

1. Visual Studio에서 솔루션(<code>MFCProject.sln</code>) 열기
2. <b>플랫폼</b>: x64 (또는 프로젝트 설정에 맞게)
3. 실행 전, <code>pch.h</code>의 <code>WindowsSizeX / WindowsSizeY</code> 확인
4. 실행
5. <b>Action</b> 기능 사용 시, 캡처 저장 경로를 코드 내부에서 필요에 맞게 수정하세요.
   - <code>OnBnClickedAction()</code> 내 <code>savePath</code> 상수 경로를 <b>사용자 PC 경로</b>로 변경 권장

<a class="backtotop" href="#top">⬆ Back to top</a>

<!-- ──────────────────────────────────────────────────────────────────────────────
  Roadmap
──────────────────────────────────────────────────────────────────────────────── -->
<h2 id="roadmap">8) 로드맵 (OpenCV 확장)</h2>

- [ ] CImage 버퍼 → OpenCV <code>cv::Mat</code> 변환 유틸 추가
- [ ] Color/Threshold 파라미터화 (검은색 외 컬러 마스크 지원)
- [ ] Contour 기반 중심/면적/바운딩 박스 측정
- [ ] 이동 경로를 <b>동영상(GIF)</b>으로 내보내기
- [ ] 딥러닝 객체 검출(YOLO 등) 연동 → <b>AI Tools Platform</b>과 REST로 연결

<a class="backtotop" href="#top">⬆ Back to top</a>


## 📝 개선점 & 배운 점 <a id="insights"></a>

- CImage 픽셀 버퍼(BGRA)를 직접 다루며 **저수준 메모리 접근과 이미지 구조**에 대한 이해를 확립했습니다.
- 좌표 이동 및 화면 갱신 과정에서 **DC(Device Context) 구조와 GDI 렌더링 흐름**을 명확히 파악했습니다.
- UI 기능을 Dialog 단위로 분리함으로써 **기능별 책임 분리와 유지보수성**의 중요성을 체감했습니다.
- 캡처 저장 경로/포맷이 코드에 고정되어 있어 → 차후 **설정 파일 또는 UI 입력 방식으로 확장**할 계획입니다.
- centroid 탐색 시 단순 RGB 조건만 사용 → 이후 **OpenCV + Threshold/Contour 기반으로 정확도 개선** 예정입니다.
- 본 프로젝트를 기반으로 **딥러닝 / Computer Vision 포트폴리오**로 확장 가능한 발판을 마련했습니다.

<a class="backtotop" href="#top">⬆ Back to top</a>

<!-- ──────────────────────────────────────────────────────────────────────────────
  Credits
──────────────────────────────────────────────────────────────────────────────── -->
<h2 id="credits">9) 크레딧</h2>

- Author: <b>서재승</b> (Seo Jae Seung)
- Email: seojaeseung9@gmail.com
- Blog: https://seungcoding.tistory.com/
- GitHub: https://github.com/jaeseung9

<a class="backtotop" href="#top">⬆ Back to top</a>

