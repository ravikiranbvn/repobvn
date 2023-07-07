// C++ program to reverse first
// k elements of a queue using dequeue.
// https://www.geeksforgeeks.org/reversing-first-k-elements-queue/
#include <deque>
#include <iostream>
#include <queue>

using namespace std;
// Function to reverse first k element of the queue
void reverseFirstK(queue<int>& q, int k)
{
	deque<int> d;

	// Dequeue the first k elements of the queue and push
	// them onto a deque
	for (int i = 0; i < k; i++) {
		d.push_front(q.front());
		q.pop();
	}

	// Pop the elements from the deque and enqueue them back
	// into the queue
	while (!d.empty()) {
		q.push(d.front());
		d.pop_front();
	}

	// Dequeue the remaining elements from the queue and
	// enqueue them back into the queue
	for (int i = 0; i < q.size() - k; i++) {
		q.push(q.front());
		q.pop();
	}
}
// Driver code.
int main()
{
	queue<int> q;
	q.push(10);
	q.push(20);
	q.push(30);
	q.push(40);
	q.push(50);
	q.push(60);
	q.push(70);
	q.push(80);
	q.push(90);
	q.push(100);

	int k = 5;

	// function call.
	reverseFirstK(q, k);

	while (!q.empty()) {
		cout << q.front() << " ";
		q.pop();
	}

    cout << "\n";
    
	return 0;
}