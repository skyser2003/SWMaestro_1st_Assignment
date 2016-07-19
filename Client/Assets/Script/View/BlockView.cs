using UnityEngine;
using UnityEngine.UI;

public class BlockView : MonoBehaviour {
    private Block block;

    private Canvas canvas;
    private Camera cam;
    private Text text;

    public void Init(Block block)
    {
        SetBlock(block);
        cam = FindObjectOfType<Camera>();
        canvas = FindObjectOfType<Canvas>();

        text = new GameObject().AddComponent<Text>();
        text.transform.SetParent(canvas.gameObject.transform);
        text.text = block.Value.ToString();
    }

    public void SetBlock(Block block)
    {
        this.block = block;
    }

    public void Refresh()
    {
        transform.position = new Vector2(block.X, block.Y);

        var uiPos = GetScreenPosition(transform, canvas, cam);
        text.transform.position = uiPos;
    }

    public static Vector3 GetScreenPosition(Transform transform, Canvas canvas, Camera cam)
    {
        Vector3 pos;
        float width = canvas.GetComponent<RectTransform>().sizeDelta.x;
        float height = canvas.GetComponent<RectTransform>().sizeDelta.y;
        float x = Camera.main.WorldToScreenPoint(transform.position).x / Screen.width;
        float y = Camera.main.WorldToScreenPoint(transform.position).y / Screen.height;
        pos = new Vector3(width * x - width / 2, y * height - height / 2);
        return pos;
    }
}