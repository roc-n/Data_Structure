/*
	应用写好的ADT实现调度队列
*/
#include "../include/Queue_task.h"
int main(void)
{
	Q queue;
	int max = 100;
	InitializeQueue(queue, max);
	ReadFile(queue); //从文件读入

	int clock = 0;			 //时钟数据
	Node *cur = queue->head; //存储头节点
	Task tmp;				 //存储暂时的结点数据

	//时间从0开始执行循环，每循环一次操作头节点一次
	while (queue->items != 0)
	{
		//首次执行
		if (cur->item.cnt == 0)
			cur->item.exe_start_time = clock; //记录执行开始时间

		cur->item.cnt++;											   //增加调用次数
		int min = (cur->item.totalTime > 2 ? 2 : cur->item.totalTime); //获取最小值
		clock += min;												   //时钟增加2
		cur->item.totalTime -= min;									   //总时间减少
		if (cur->item.totalTime == 0)								   //执行完毕出队列
		{
			cur->item.exe_end_time = clock;
			OutFile(queue); //输出信息到文件
			DeQueue(queue, tmp);
			cur = queue->head;
		}
		else if (queue->items == 1) //若只有一个结点就一直循环直至操作完毕
			continue;
		else //将队首调至队尾
			HeadToRear(queue, cur);
	}
	cout << "Done" << endl;
}