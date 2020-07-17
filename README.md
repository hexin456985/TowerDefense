Towerdenfense 塔防游戏 

一．项目说明 


  Fantasy是我们设计的一个塔防游戏的桌面程序，主要利用Qt作为程序开发的框架。游戏规则与大部分塔防游戏相同，通过在地图上建造防御塔等建筑物，以阻止游戏中敌人进攻的策略型游戏，且我们设计多种形态和特性的防御塔和怪兽，和几个不同难度的地图，还加入了升级防御塔的功能，为整体游戏增加趣味性和耐玩性。

二．项目工具 


编译软件：Visual Studio

版本控制：Git, Github

开发环境：QT 5.9.0 

编程语言：C++ 17 

框架结构：MVVM结构

成员沟通：钉钉群组


三. 项目设计


1.游戏设计


（1）游戏显示界面

游戏开始界面

游戏选关界面

游戏主界面（根据选关不同会有不同的主界面）


（2）游戏规则

玩家通过金币在可以放置的范围放置防御塔，分别有四种不同形态属性的防御塔：

普通塔（发射箭矢），冰冻塔（发射冰冻光束，具有缓速功能），地狱塔（发射火球，高伤害近距离），迫击炮塔（发射火炮，高伤害远程塔）

建造塔所需要的金币递增，玩家通过击败怪物取得金币

玩家不仅可以放置防御塔，还可以升级按键和删除按键分别升级防御塔和删除已放防御塔，防御塔总共可以升级至两级，升级后各项数据都会有相应的提升


玩家需要面对怪物的进攻且防御主塔

怪物总共有五种能力不同的怪物，且会按照地图中的路径移动

怪物按照能力依次分为：普通怪，血量低高移速怪，血量高移速慢怪，高赏金怪，大Boss

怪物群会随着波次的不同和关卡的升级而产生改变

怪物路径的终点为己方的主塔，主塔会随着血量的降低而产生5种不同形态的变化，用来提示玩家主塔的血量变化


（3）其他配置

音乐配置：开场音乐，失败音乐，胜利音乐，有序进行音乐等

音效配置：防御塔攻击音效，怪物受伤音效等


四. 实现思路


1 游戏构成

防御塔，子弹，怪物，游戏界面，多功能按键

2 游戏实现

（1）选关页面通过几个关卡数字的按钮分别进去不同的游戏界面

（2）进入游戏界面后，地图被划分为塔放置区域，怪物行径路线，玩家属性和装备区域，和地图中无用区域

（3）初始化 - 放置塔区域为空，怪物从路径起点开始出现，主塔血量为满格，金币数量为刚开始的一个定值

（4）主要事件：塔发射子弹，怪物受伤死亡，主塔的损耗，塔的升级与删除



五．框架描述 


框架采用MVVM模式，分为Commmon,App,View,View Model与Model层

Common和App层主要负责Window的交互界面部分和有关显示部分的内容；

View Model和View负责作为上下层的接口，和进行数据转换，在游戏中主要体现在按钮输入，防御塔攻击与升级，重生怪物与巡线，游戏路径分析等方面，

Model层负责底层数据处理，在游戏中主要体现在怪物血量计算，防御塔相关数值，主塔生命值计算，怪物攻击波计算等数值设计方面。


六．实施方案


1.第一轮迭代：完成防御塔，主塔，子弹，怪物的基础设定和有关交互界面的设定

2.第二轮迭代：完成开始画面，选关画面，开始、选关功能，游戏声音

3.第三轮迭代：完成游戏画面，设计地图中的防御塔可放位置和怪物路线 

4.第四轮迭代：完成剩余细小功能：删除防御塔，升级防御塔，怪物波次等 

5.第五轮迭代：优化游戏细节，修复遇到的问题



七．项目分工：

Common,App: 曾致语 ；View Model,View: 孙家阳；Model: 朱允怀
