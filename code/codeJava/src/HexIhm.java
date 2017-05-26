
import java.awt.Graphics;
import java.awt.Image;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.JPanel;
import java.awt.Color;


public class HexIhm extends JPanel {
    private int[] x = {20, 35, 35, 20, 5, 5};
    private int[] y = {5, 15, 25, 35, 25, 15};
    private int turn = 1;
    private int hexSize = 30;
    private int boardSize;
    private boolean ok = false;
    private Color c = Color.red;
    int []xBases;
    int []yBases;
    public HexIhm(int boardSize) {
        this.boardSize = boardSize;
    }

    public void paintComponent(Graphics g) {
        BufferedImage buf = new BufferedImage(80, 70, BufferedImage.TYPE_INT_ARGB);

        int[] xBase = {20, 35, 35, 20, 5, 5};
        int[] yBase = {5, 15, 25, 35, 25, 15};

        for (int i = 0; i < boardSize * boardSize; i++) {
            if (i % boardSize == 0 && i != 0) {
                xBase = initXTab(x, turn);
                // printTab(xBase);
                yBase = initYTab(y, turn);
                turn++;
            }
            g.drawPolygon(xBase, yBase, 6);
            xBase = incXTab(xBase);
        }
        if (ok) {
            repaint(g, c, xBases, yBases);
        }
    }

    public void setXbas(int [] xBase) {
        this.xBases = xBase;
    }
    public void setYbas(int [] yBase) {
        this.yBases = yBase;
    }

    public void setColor(Color c) {
        this.c = c;
    }

    public void repaint(Graphics g, Color c, int []xBase, int []yBase) {
        g.setColor(c);
        g.fillPolygon(xBase, yBase, 6);
    }

    public int[] initXTab(int[] x, int turn) {
        int [] xb = new int[6];
        for (int i = 0; i < 6; i++) {
            xb[i] = x[i] + (turn * (hexSize / 2));
        }
        return xb;
    }

    public int[] initYTab(int[] y, int turn) {
        int [] yb = new int[6];
        for (int i = 0; i < 6; i++) {
            yb[i] = y[i] + (turn * ((hexSize / 3) * 2));
        }
        return yb;
    }

    public int[] incXTab(int[] xb) {
        for (int i = 0; i < 6; i++) {
            xb[i] += hexSize;
        }
        return xb;
    }

    void setRepaint(boolean ok) {
        this.ok = ok;
    }
    // Graphics getG(){
    //     return this.g;
    // }

    public void printTab(int[] tab) {
        for (int i = 0; i < tab.length; i++) {
            System.out.println(i + " " + tab[i]);
        }
    }
}
