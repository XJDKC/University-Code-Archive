import java.util.Stack;
import java.util.NoSuchElementException;


public class Queue<E> extends Stack<E> implements Cloneable {
    public final int dump = 10;
    private Stack<E> stk;

    public Queue() {
        stk = new Stack<E>();
    }

    public boolean add(E e) throws IllegalStateException, ClassCastException,
            NullPointerException, IllegalArgumentException {
        if (e == null)
            throw new NullPointerException();

        if (stk.size() < dump) {
            stk.push(e);
            return true;
        }
        if (super.empty()) {
            while (stk.size() > 0)
                this.push(stk.pop());
            stk.push(e);
            return true;
        } else
            throw new IllegalStateException("Full!");
    }

    public boolean offer(E e) throws ClassCastException, NullPointerException,
            IllegalArgumentException {
        if (e == null)
            throw new NullPointerException();

        if (stk.size() < dump) {
            stk.push(e);
            return true;
        }
        if (super.empty()) {
            while (!stk.empty())
                this.push(stk.pop());
            stk.push(e);
            return true;
        } else
            return false;
    }

    public E remove() throws NoSuchElementException {
        if (!super.empty()) {
            return this.pop();
        }
        if (!stk.empty()) {
            while (!stk.empty()) {
                this.push(stk.pop());
            }
            return this.pop();
        } else
            throw new NoSuchElementException("Empty!");
    }

    public E poll() {
        if (!super.empty()) {
            return this.pop();
        }
        if (!stk.empty()) {
            while (!stk.empty()) {
                this.push(stk.pop());
            }
            return this.pop();
        } else
            return null;
    }

    public E element() throws NoSuchElementException {
        if (!super.empty()) {
            return super.peek();
        }
        if (!stk.empty()) {
            while (!stk.empty()) {
                this.push(stk.pop());
            }
            return super.peek();
        } else
            throw new NoSuchElementException("Empty!");
    }

    public E peek() {
        if (!super.empty()) {
            return super.peek();
            //return this.elementAt(super.size() - 1);
        }
        if (!stk.empty()) {
            while (!stk.empty()) {
                super.push(stk.pop());
            }
            return super.peek();
            //return this.elementAt(super.size() - 1);
        } else
            return null;
    }
}
