public class Block {
    public int X, Y;

    public int Value { get; private set; }

    public Block(int value)
    {
        Value = value;
    }

    public void Add(Block other)
    {
        Value += other.Value;
    }
}