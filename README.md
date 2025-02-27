## 📌 목차  
- [1. 콘솔 프로그래밍](#console)  <br/>
- [2. 콘솔 알고리즘 프로그래밍](#console-algo)  <br/>

<details>
  <summary><h2 id="console"><b>1개월차 콘솔 프로그래밍</b></h2></summary>

   ## ⍩⃝팩맨 제작
   <p align="center">
     ▼아래 팩맨을 클릭하시면 팩맨 소스코드로 들어갑니다!▼<br/>
     <a href="https://github.com/sansitasan/WantedLecture/tree/main/PackMan" target="_blank">
     <img src="https://github.com/user-attachments/assets/65fe3afc-3162-4688-9570-559e36f6bad6" width="400px">
     </p>
     </a>

  > <details>
  >   <summary><h3>🛠 주요 작업</h3></summary>
  >   
  > >   <details>
  > >    <summary>MemoryPool 제작</summary>
  > >    - 템플릿으로 생성, 삭제가 빈번한 객체들에게 사용할 수 있도록 제작<br/>  
  > >    - 메모리를 잡아두고, 부족할 때마다 공간을 2배로 확장<br/>  
  > >    - `Placement new` 활용하여 미리 확보된 공간에 객체 생성<br/>  
  > >    <p align="center">
  > >      <img src="https://github.com/user-attachments/assets/b4c17d18-e3ea-408f-b2c1-5875a0de8e5b" width="400px">
  > >      <img src="https://github.com/user-attachments/assets/ab0455ef-a5ba-4d79-a2a3-702876eac62f" width="400px">
  > >    </p>
  > >  </details>
  >   
  > >  <details>
  > >    <summary>BT 활용 AI 제작</summary>
  > >    - Node들의 조건 체크로 실행 노드 결정<br/>  
  > >    - 적의 방향을 확률적으로 전환하며 AI 구현<br/>  
  > >    - 플레이어가 근처에 있으면 방향 전환<br/>  
  > >    - 아이템을 먹었다면, 플레이어와 먼 곳으로 도망<br/>  
  > >    <p align="center">
  > >      <img src="https://github.com/user-attachments/assets/ef07f652-d1d7-4e03-abb7-a7f43337a2b1" width="400px">
  > >      <img src="https://github.com/user-attachments/assets/b99a6a93-8769-4b4d-b825-8dd0f989d3da" width="400px">
  > >    </p>
  > >  </details>
  >   
  > >  <details>
  > >    <summary>함수 포인터를 활용한 인풋 매니저, 코루틴 제작</summary>
  > >    - 키와 함수, 객체 타입을 바인딩 후 엔진 내 변수에 등록<br/>  
  > >    - 매 프레임 키 상태를 체크하여 적절한 함수 실행<br/>  
  > >    - 실행할 함수와 객체 타입, 시간과 반복 여부를 받아 타이머 매니저에 등록<br/>  
  > >    - 타이머 매니저는 MemoryPool 사용<br/>  
  > >    <p align="center">
  > >      <img src="https://github.com/user-attachments/assets/156f7453-0390-43fe-97ce-be2a2e8f8967" width="400px">
  > >      <img src="https://github.com/user-attachments/assets/305459d0-3af2-492a-aa8b-a2d533297ca9" width="400px">
  > >      <img src="https://github.com/user-attachments/assets/a470f9b9-97fa-46b2-ac4c-ed134c63382d" width="800px">
  > >    </p>
  > >  </details>
  >   
  > </details>
  > 
  > <details>
  >   <summary><h3>🚨 이슈/해결</h3></summary>
  >   
  > >  <details>
  > >    <summary>적 AI가 같은 자리에서 계속 움직이는 현상</summary>
  > >    - 매 프레임 랜덤 방향 결정으로 인해 발생<br/>  
  > >    - 한 칸마다 방향을 결정하거나 갈림길에서 방향 결정하여 해결<br/>  
  > >  </details>
  >   
  > >  <details>
  > >    <summary>플레이어를 쫓거나 도망칠 때 프레임 드랍 발생</summary>
  > >    - 매 프레임 A* 사용으로 과부하 발생<br/>  
  > >    - 특정 범위 내에서 방향을 정하고 탐색하는 방식으로 해결<br/>  
  > >  </details>
  >   
  > >  <details>
  > >    <summary>Placement new 사용 시 컴파일 오류 발생</summary>
  > >    - new를 memory leak 확인을 위해 매크로로 변경하여 발생<br/>  
  > >    - 매크로에서 사용하는 이름을 전부 변경하여 해결<br/>  
  > >  </details>
  >   
  > >  <details>
  > >    <summary>Scene 전환 시에도 플레이어가 입력을 받는 문제</summary>
  > >    - 함수 포인터 실행 시 active 여부 검사 누락<br/>  
  > >    - 객체별 active 상태를 체크하는 bool 변수를 추가하여 해결<br/>  
  > >  </details>
  >   
  > >  <details>
  > >    <summary>Switch 문 중간에 객체 정의 시 에러</summary>
  > >    - switch 문에서 중괄호 없이 case를 사용할 경우 발생<br/>  
  > >    - 객체 정의를 하는 case는 중괄호로 감싸 해결<br/>  
  > >  </details>
  >   
  > </details>

</details><br/>

<details>
  <summary><h2 id="console-algo"><b>2개월차 콘솔 알고리즘 프로그래밍</b></h2></summary>

   ## 🚀미사일 제작
   <p align="center">
     ▼아래 타이틀을 클릭하시면 미사일 소스코드로 들어갑니다!▼<br/>
     <a href="https://github.com/sansitasan/WantedLecture/tree/main/Missile" target="_blank">
     <img src="https://github.com/user-attachments/assets/d252d663-c6f7-45b7-bc8b-d36e424b125a" width="400px">
     </p>
     </a>

  > <details>
  >   <summary><h3>🛠 주요 작업</h3></summary>
  >   
  > >   <details>
  > >    <summary>SIMD 연산</summary>
  > >    - Vector2, Vector3 구조체의 연산 속도 최적화를 위해 도입<br/>  
  > >    - Vector2는 멤버 변수로 float 둘만을 가짐, 따라서 64비트를 사용하는 __m64를 사용하고 싶었으나, __m64는 부동소수점 연산을 지원하지 않음<br/>  
  > >    - 따라서 128비트를 사용하는 __m128과 float 2개를 사용하는 기존 연산의 성능 비교를 해보았고, 연산들이 평균적으로 20~25%가량 성능 향상이 있었음<br/>
  > >    <p align="center">
  > >      <img src="https://github.com/user-attachments/assets/b4c17d18-e3ea-408f-b2c1-5875a0de8e5b" width="400px">
  > >      <img src="https://github.com/user-attachments/assets/ab0455ef-a5ba-4d79-a2a3-702876eac62f" width="400px">
  > >    </p>
  > >  </details>
  >   
  > >  <details>
  > >    <summary>A*</summary>
  > >    - OpenList, CloseList를 각각 pq와, unordered_map으로 최적화<br/>  
  > >    - OpenList를 set으로 제작하고 싶었으나, 비교 함수 객체를 fCost로 비교하도록 설정하여 fCost가 같을 경우 같은 노드로 인식하는 문제 발생<br/>
  > >    - 이를 변경하는 방법은 MultiSet과 pq가 있었고, 이 선택의 결정권은 이웃 노드의 추가 전 OpenList에 중복 여부를 확인하는 것이었다. 여기서 굳이 순회를 하며 여부 확인을 하는 것은 오히려 비용이 더 나올 것으로 예상되었다.(비교 연산 한 번, CloseList 확인 O(1) vs OpenList 순회 O(k))<br/>  
  > >    - 따라서 MultiSet과 pq중 pq를 선택하게 되었다.<br/>  
  > >    - 타이머 매니저는 MemoryPool 사용<br/>  
  > >    <p align="center">
  > >      <img src="https://github.com/user-attachments/assets/1a3702eb-f52f-4099-9210-925d6f550230" width="400px">
  > >      <img src="https://github.com/user-attachments/assets/5854b10d-28c6-43ab-a36c-3891e3aac66a" width="400px">
  > >    </p>
  > >  </details>
  >
  > >  <details>
  > >    <summary>QuadTree</summary>
  > >    - 많은 미사일이 하나하나 A* 연산을 하면 시간이 오래 걸리기에, 마우스 포인터 주변에 있는 미사일만  A*를 실행시킬 수 있도록 QuadTree를 추가<br/>  
  > >    - 마우스 클릭 시 해당 영역의 자식 노드를 Max Depth까지 생성하고, 마우스 위치를 트리에 추가<br/>  
  > >    - 재클릭시 쿼드 트리의 마우스 위치를 제거하고 다시 현재 위치로 추가<br/>  
  > >    - A*가 활성화되어 있다면 미사일이 트리에서 마우스 위치를 가져올 수 있으면 가져와서 A* 실행<br/>  
  > >    <p align="center">
  > >      <img src="https://github.com/user-attachments/assets/3bb1b33d-a66c-4b83-bf20-cc0b4d3a8a97" width="400px">
  > >    </p>
  > >  </details>
  >
  > >  <details>
  > >    <summary>Curve</summary>
  > >    - 베지어 곡선과 허밋 곡선 추가<br/>  
  > >    - 미사일 위치와 마우스 위치를 시작점, 끝점으로 잡고 시작점과 끝점을 뺀 벡터를 회전시켜 접선 벡터로 활용<br/>  
  > >    - 이를 공식에 대입하고, t값을 시간 대신 등속 운동을 위한 속도 / 거리를 주었다.<br/>
  > >    <p align="center">
  > >      <img src="https://github.com/user-attachments/assets/a9c4b304-d652-4f12-9834-a79be71137be" width="400px">
  > >    </p>
  > >  </details>
  >   
  > </details>
  >
  > <details>
  >   <summary><h3>🚨 이슈/해결</h3></summary>
  >   
  > >  <details>
  > >    <summary>적 AI가 같은 자리에서 계속 움직이는 현상</summary>
  > >    - 매 프레임 랜덤 방향 결정으로 인해 발생<br/>  
  > >    - 한 칸마다 방향을 결정하거나 갈림길에서 방향 결정하여 해결<br/>  
  > >  </details>
  >   
  > >  <details>
  > >    <summary>플레이어를 쫓거나 도망칠 때 프레임 드랍 발생</summary>
  > >    - 매 프레임 A* 사용으로 과부하 발생<br/>  
  > >    - 특정 범위 내에서 방향을 정하고 탐색하는 방식으로 해결<br/>  
  > >  </details>
  >   
  > >  <details>
  > >    <summary>Placement new 사용 시 컴파일 오류 발생</summary>
  > >    - new를 memory leak 확인을 위해 매크로로 변경하여 발생<br/>  
  > >    - 매크로에서 사용하는 이름을 전부 변경하여 해결<br/>  
  > >  </details>
  >   
  > >  <details>
  > >    <summary>Scene 전환 시에도 플레이어가 입력을 받는 문제</summary>
  > >    - 함수 포인터 실행 시 active 여부 검사 누락<br/>  
  > >    - 객체별 active 상태를 체크하는 bool 변수를 추가하여 해결<br/>  
  > >  </details>
  >   
  > >  <details>
  > >    <summary>Switch 문 중간에 객체 정의 시 에러</summary>
  > >    - switch 문에서 중괄호 없이 case를 사용할 경우 발생<br/>  
  > >    - 객체 정의를 하는 case는 중괄호로 감싸 해결<br/>  
  > >  </details>
  >   
  > </details>

</details>
