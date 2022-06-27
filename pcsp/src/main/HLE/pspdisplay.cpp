/*
* 27/06/2022 - Ported from jpscp 2a9c39b0(16/09/2008)
* 
*/
#include "pspdisplay.h"

/*TODO*/  // public final class pspdisplay extends GLCanvas implements GLEventListener {
/*TODO*/  //    private static pspdisplay instance;
/*TODO*/  //    public static pspdisplay get_instance() {
/*TODO*/  //        if (instance == null)
/*TODO*/  //            instance = new pspdisplay();
/*TODO*/  //        return instance;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    // PspDisplayPixelFormats enum
/*TODO*/  //    public static final int PSP_DISPLAY_PIXEL_FORMAT_565  = 0;
/*TODO*/  //    public static final int PSP_DISPLAY_PIXEL_FORMAT_5551 = 1;
/*TODO*/  //    public static final int PSP_DISPLAY_PIXEL_FORMAT_4444 = 2;
/*TODO*/  //    public static final int PSP_DISPLAY_PIXEL_FORMAT_8888 = 3;
/*TODO*/  //
/*TODO*/  //    // PspDisplaySetBufSync enum
/*TODO*/  //    public static final int PSP_DISPLAY_SETBUF_IMMEDIATE = 0;
/*TODO*/  //    public static final int PSP_DISPLAY_SETBUF_NEXTFRAME = 1;
/*TODO*/  //
/*TODO*/  //    // PspDisplayErrorCodes enum
/*TODO*/  //    public static final int PSP_DISPLAY_ERROR_OK       = 0;
/*TODO*/  //    public static final int PSP_DISPLAY_ERROR_POINTER  = 0x80000103;
/*TODO*/  //    public static final int PSP_DISPLAY_ERROR_ARGUMENT = 0x80000107;
/*TODO*/  //
/*TODO*/  //    public boolean disableGE;
/*TODO*/  //
/*TODO*/  //    // current display mode
/*TODO*/  //    private int mode;
/*TODO*/  //    private int width;
/*TODO*/  //    private int height;
/*TODO*/  //
/*TODO*/  //    // current framebuffer settings
/*TODO*/  //    private int topaddr;
/*TODO*/  //    private int bufferwidth;
/*TODO*/  //    private int pixelformat;
/*TODO*/  //    private int sync;
/*TODO*/  //
/*TODO*/  //    // additional variables
/*TODO*/  //    private int bottomaddr;
/*TODO*/  //    private boolean refreshRequired;
/*TODO*/  //    private long lastUpdate;
/*TODO*/  //
/*TODO*/  //    // Canvas fields
/*TODO*/  //    private ByteBuffer pixels;
/*TODO*/  //    private ByteBuffer temp;
/*TODO*/  //    private int canvasWidth;
/*TODO*/  //    private int canvasHeight;
/*TODO*/  //    private boolean createTex;
/*TODO*/  //    private int texFb;
/*TODO*/  //    private float texS;
/*TODO*/  //    private float texT;
/*TODO*/  //
/*TODO*/  //    // fps counter variables
/*TODO*/  //    private long prevStatsTime = 0;
/*TODO*/  //    private long frameCount = 0;
/*TODO*/  //    private long actualframeCount = 0;
/*TODO*/  //    private long reportCount = 0;
/*TODO*/  //    private double averageFPS = 0.0;
/*TODO*/  //
/*TODO*/  //    private pspdisplay() {
/*TODO*/  //        setSize(480, 272);
/*TODO*/  //        addGLEventListener(this);
/*TODO*/  //        texFb = -1;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void Initialise() {
/*TODO*/  //        mode        = 0;
/*TODO*/  //        width       = 480;
/*TODO*/  //        height      = 272;
/*TODO*/  //        topaddr     = MemoryMap.START_VRAM;
/*TODO*/  //        bufferwidth = 512;
/*TODO*/  //        pixelformat = PSP_DISPLAY_PIXEL_FORMAT_8888;
/*TODO*/  //        sync        = PSP_DISPLAY_SETBUF_IMMEDIATE;
/*TODO*/  //
/*TODO*/  //        bottomaddr =
/*TODO*/  //            topaddr + bufferwidth * height * getPixelFormatBytes(pixelformat);
/*TODO*/  //
/*TODO*/  //        refreshRequired = true;
/*TODO*/  //        createTex = true;
/*TODO*/  //
/*TODO*/  //        disableGE =
/*TODO*/  //            Settings.get_instance().readBoolOptions("emuoptions/disablege");
/*TODO*/  //
/*TODO*/  //        getPixels();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void step() {
/*TODO*/  //        long now = System.currentTimeMillis();
/*TODO*/  //        if (now - lastUpdate > 1000 / 60) {
/*TODO*/  //            if (refreshRequired) {
/*TODO*/  //                display();
/*TODO*/  //                refreshRequired = false;
/*TODO*/  //            }
/*TODO*/  //            lastUpdate = now;
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void write8(int address, int data) {
/*TODO*/  //        address &= 0x3FFFFFFF;
/*TODO*/  //        if (address >= topaddr && address < bottomaddr)
/*TODO*/  //            setDirty(true);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void write16(int address, int data) {
/*TODO*/  //        address &= 0x3FFFFFFF;
/*TODO*/  //        if (address >= topaddr && address < bottomaddr)
/*TODO*/  //            setDirty(true);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void write32(int address, int data) {
/*TODO*/  //        address &= 0x3FFFFFFF;
/*TODO*/  //        if (address >= topaddr && address < bottomaddr)
/*TODO*/  //            setDirty(true);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void setDirty(boolean dirty) {
/*TODO*/  //        refreshRequired = dirty;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private static int getPixelFormatBytes(int pixelformat) {
/*TODO*/  //        return pixelformat == PSP_DISPLAY_PIXEL_FORMAT_8888 ? 4 : 2;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private static int getPixelFormatGL(int pixelformat) {
/*TODO*/  //        switch (pixelformat) {
/*TODO*/  //        case PSP_DISPLAY_PIXEL_FORMAT_565:
/*TODO*/  //            return GL.GL_UNSIGNED_SHORT_5_6_5_REV;
/*TODO*/  //        case PSP_DISPLAY_PIXEL_FORMAT_5551:
/*TODO*/  //            return GL.GL_UNSIGNED_SHORT_1_5_5_5_REV;
/*TODO*/  //        case PSP_DISPLAY_PIXEL_FORMAT_4444:
/*TODO*/  //            return GL.GL_UNSIGNED_SHORT_4_4_4_4_REV;
/*TODO*/  //        default:
/*TODO*/  //            return GL.GL_UNSIGNED_BYTE;
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void getPixels() {
/*TODO*/  //        Memory memory = Emulator.getMemory();
/*TODO*/  //        byte[] all = memory.videoram.array();
/*TODO*/  //        pixels = ByteBuffer.wrap(
/*TODO*/  //            all,
/*TODO*/  //            topaddr - MemoryMap.START_VRAM + memory.videoram.arrayOffset(),
/*TODO*/  //            bottomaddr - topaddr).slice();
/*TODO*/  //        pixels.order(ByteOrder.LITTLE_ENDIAN);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private int makePow2(int n) {
/*TODO*/  //        --n;
/*TODO*/  //        n = (n >>  1) | n;
/*TODO*/  //        n = (n >>  2) | n;
/*TODO*/  //        n = (n >>  4) | n;
/*TODO*/  //        n = (n >>  8) | n;
/*TODO*/  //        n = (n >> 16) | n;
/*TODO*/  //        return ++n;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void reportFPSStats() {
/*TODO*/  //        frameCount++;
/*TODO*/  //        long timeNow = System.nanoTime();
/*TODO*/  //        long realElapsedTime = (timeNow - prevStatsTime) / 1000000L;
/*TODO*/  //
/*TODO*/  //        if (realElapsedTime > 1000L) {
/*TODO*/  //            reportCount++;
/*TODO*/  //            int lastFPS = (int)(frameCount - actualframeCount);
/*TODO*/  //            averageFPS = (double)frameCount / reportCount;
/*TODO*/  //            actualframeCount = frameCount;
/*TODO*/  //            prevStatsTime = timeNow;
/*TODO*/  //
/*TODO*/  //            Emulator.setFpsTitle("averageFPS: " + String.format("%.1f", averageFPS) + " lastFPS: " +
          //            lastFPS);
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void drawFrameBuffer(final GL gl, boolean first, boolean invert) {
/*TODO*/  //        gl.glPushAttrib(GL.GL_ALL_ATTRIB_BITS);
/*TODO*/  //
/*TODO*/  //        if (first)
/*TODO*/  //            gl.glViewport(0, 0, width, height);
/*TODO*/  //        else
/*TODO*/  //            gl.glViewport(0, 0, canvasWidth, canvasHeight);
/*TODO*/  //
/*TODO*/  //        gl.glDisable(GL.GL_DEPTH_TEST);
/*TODO*/  //
/*TODO*/  //        gl.glMatrixMode(GL.GL_PROJECTION);
/*TODO*/  //        gl.glPushMatrix();
/*TODO*/  //        gl.glLoadIdentity();
/*TODO*/  //
/*TODO*/  //        if (invert)
/*TODO*/  //            gl.glOrtho(0.0, width, height, 0.0, -1.0, 1.0);
/*TODO*/  //        else
/*TODO*/  //            gl.glOrtho(0.0, width, 0.0, height, -1.0, 1.0);
/*TODO*/  //
/*TODO*/  //        gl.glMatrixMode(GL.GL_MODELVIEW);
/*TODO*/  //        gl.glPushMatrix();
/*TODO*/  //        gl.glLoadIdentity();
/*TODO*/  //
/*TODO*/  //        gl.glEnable(GL.GL_TEXTURE_2D);
/*TODO*/  //        gl.glBindTexture(GL.GL_TEXTURE_2D, texFb);
/*TODO*/  //        gl.glBegin(GL.GL_QUADS);
/*TODO*/  //
/*TODO*/  //        gl.glColor3f(1.0f, 1.0f, 1.0f);
/*TODO*/  //
/*TODO*/  //        gl.glTexCoord2f(0.0f, 0.0f);
/*TODO*/  //        gl.glVertex2f(0.0f, 0.0f);
/*TODO*/  //
/*TODO*/  //        gl.glTexCoord2f(0.0f, texT);
/*TODO*/  //        gl.glVertex2f(0.0f, height);
/*TODO*/  //
/*TODO*/  //        gl.glTexCoord2f(texS, texT);
/*TODO*/  //        gl.glVertex2f(width, height);
/*TODO*/  //
/*TODO*/  //        gl.glTexCoord2f(texS, 0.0f);
/*TODO*/  //        gl.glVertex2f(width, 0.0f);
/*TODO*/  //
/*TODO*/  //        gl.glEnd();
/*TODO*/  //
/*TODO*/  //        gl.glMatrixMode(GL.GL_MODELVIEW);
/*TODO*/  //        gl.glPopMatrix();
/*TODO*/  //        gl.glMatrixMode(GL.GL_PROJECTION);
/*TODO*/  //        gl.glPopMatrix();
/*TODO*/  //        gl.glMatrixMode(GL.GL_MODELVIEW);
/*TODO*/  //        gl.glPopAttrib();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    // GLEventListener methods
/*TODO*/  //
/*TODO*/  //    @Override
/*TODO*/  //    public void init(GLAutoDrawable drawable) {
/*TODO*/  //        final GL gl = drawable.getGL();
/*TODO*/  //        gl.setSwapInterval(1);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @Override
/*TODO*/  //    public void display(GLAutoDrawable drawable) {
/*TODO*/  //        final GL gl = drawable.getGL();
/*TODO*/  //
/*TODO*/  //        if (createTex) {
/*TODO*/  //            int[] textures = new int[1];
/*TODO*/  //            if (texFb != -1) {
/*TODO*/  //                textures[0] = texFb;
/*TODO*/  //                gl.glDeleteTextures(1, textures, 0);
/*TODO*/  //            }
/*TODO*/  //            gl.glGenTextures(1, textures, 0);
/*TODO*/  //            texFb = textures[0];
/*TODO*/  //
/*TODO*/  //            gl.glBindTexture(GL.GL_TEXTURE_2D, texFb);
/*TODO*/  //            gl.glTexImage2D(
/*TODO*/  //                GL.GL_TEXTURE_2D, 0,
/*TODO*/  //                GL.GL_RGBA,
/*TODO*/  //                bufferwidth, makePow2(height), 0,
/*TODO*/  //                GL.GL_RGBA,
/*TODO*/  //                getPixelFormatGL(pixelformat), null);
/*TODO*/  //            gl.glTexParameteri(
/*TODO*/  //                GL.GL_TEXTURE_2D, GL.GL_TEXTURE_MIN_FILTER, GL.GL_NEAREST);
/*TODO*/  //            gl.glTexParameteri(
/*TODO*/  //                GL.GL_TEXTURE_2D, GL.GL_TEXTURE_MAG_FILTER, GL.GL_NEAREST);
/*TODO*/  //            gl.glTexParameteri(
/*TODO*/  //                GL.GL_TEXTURE_2D, GL.GL_TEXTURE_WRAP_S, GL.GL_CLAMP);
/*TODO*/  //            gl.glTexParameteri(
/*TODO*/  //                GL.GL_TEXTURE_2D, GL.GL_TEXTURE_WRAP_T, GL.GL_CLAMP);
/*TODO*/  //
/*TODO*/  //            temp = ByteBuffer.allocate(
/*TODO*/  //                bufferwidth * makePow2(height) *
/*TODO*/  //                getPixelFormatBytes(pixelformat));
/*TODO*/  //            temp.order(ByteOrder.LITTLE_ENDIAN);
/*TODO*/  //
/*TODO*/  //            createTex = false;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (texFb == -1) {
/*TODO*/  //            gl.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
/*TODO*/  //            gl.glClear(GL.GL_COLOR_BUFFER_BIT);
/*TODO*/  //            return;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        pixels.clear();
/*TODO*/  //        gl.glTexSubImage2D(
/*TODO*/  //            GL.GL_TEXTURE_2D, 0,
/*TODO*/  //            0, 0, bufferwidth, height,
/*TODO*/  //            GL.GL_RGBA, getPixelFormatGL(pixelformat), pixels);
/*TODO*/  //
/*TODO*/  //        if (disableGE) {
/*TODO*/  //            drawFrameBuffer(gl, false, true);
/*TODO*/  //        } else {
/*TODO*/  //            drawFrameBuffer(gl, true, true);
/*TODO*/  //
/*TODO*/  //            gl.glViewport(0, 0, width, height);
/*TODO*/  //            VideoEngine.getEngine(gl, true, true).update();
/*TODO*/  //
/*TODO*/  //            gl.glBindTexture(GL.GL_TEXTURE_2D, texFb);
/*TODO*/  //            gl.glCopyTexSubImage2D(
/*TODO*/  //                GL.GL_TEXTURE_2D, 0,
/*TODO*/  //                0, 0, 0, 0, width, height);
/*TODO*/  //
/*TODO*/  //            temp.clear();
/*TODO*/  //            pixels.clear();
/*TODO*/  //            gl.glGetTexImage(
/*TODO*/  //                GL.GL_TEXTURE_2D, 0, GL.GL_RGBA,
/*TODO*/  //                getPixelFormatGL(pixelformat), temp);
/*TODO*/  //            temp.put(pixels);
/*TODO*/  //            drawFrameBuffer(gl, false, false);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        reportFPSStats();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @Override
/*TODO*/  //    public void reshape(
/*TODO*/  //        GLAutoDrawable drawable,
/*TODO*/  //        int x, int y,
/*TODO*/  //        int width, int height)
/*TODO*/  //    {
/*TODO*/  //        canvasWidth  = width;
/*TODO*/  //        canvasHeight = height;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @Override
/*TODO*/  //    public void displayChanged(
/*TODO*/  //        GLAutoDrawable drawable,
/*TODO*/  //        boolean modeChanged,
/*TODO*/  //        boolean displayChanged)
/*TODO*/  //    {
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    // HLE functions
/*TODO*/  //
/*TODO*/  //    public void sceDisplaySetMode(int mode, int width, int height) {
/*TODO*/  //        System.out.println(
/*TODO*/  //            "sceDisplaySetMode(mode=" + mode +
/*TODO*/  //            ",width=" + width +
/*TODO*/  //            ",height=" + height + ")");
/*TODO*/  //
/*TODO*/  //        if (width <= 0 || height <= 0) {
/*TODO*/  //            Emulator.getProcessor().gpr[2] = -1;
/*TODO*/  //        } else {
/*TODO*/  //            this.mode   = mode;
/*TODO*/  //            this.width  = width;
/*TODO*/  //            this.height = height;
/*TODO*/  //
/*TODO*/  //            bottomaddr =
/*TODO*/  //                topaddr + bufferwidth * height *
/*TODO*/  //                getPixelFormatBytes(pixelformat);
/*TODO*/  //
/*TODO*/  //            refreshRequired = true;
/*TODO*/  //
/*TODO*/  //            Emulator.getProcessor().gpr[2] = 0;
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void sceDisplayGetMode(int pmode, int pwidth, int pheight) {
/*TODO*/  //        Memory memory = Emulator.getMemory();
/*TODO*/  //        if (!memory.isAddressGood(pmode  ) ||
/*TODO*/  //            !memory.isAddressGood(pwidth ) ||
/*TODO*/  //            !memory.isAddressGood(pheight))
/*TODO*/  //        {
/*TODO*/  //            Emulator.getProcessor().gpr[2] = -1;
/*TODO*/  //        } else {
/*TODO*/  //            memory.write32(pmode  , mode  );
/*TODO*/  //            memory.write32(pwidth , width );
/*TODO*/  //            memory.write32(pheight, height);
/*TODO*/  //            Emulator.getProcessor().gpr[2] = 0;
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void sceDisplaySetFrameBuf(
/*TODO*/  //        int topaddr, int bufferwidth, int pixelformat, int sync)
/*TODO*/  //    {
/*TODO*/  //        topaddr &= 0x3FFFFFFF;
/*TODO*/  //        if (topaddr < MemoryMap.START_VRAM || topaddr >= MemoryMap.END_VRAM ||
/*TODO*/  //            bufferwidth <= 0 || (bufferwidth & (bufferwidth - 1)) != 0 ||
/*TODO*/  //            pixelformat < 0 || pixelformat > 3 ||
/*TODO*/  //            sync < 0 || sync > 1)
/*TODO*/  //        {
/*TODO*/  //            Emulator.getProcessor().gpr[2] = -1;
/*TODO*/  //        } else {
/*TODO*/  //            if (pixelformat != this.pixelformat ||
/*TODO*/  //                bufferwidth != this.bufferwidth ||
/*TODO*/  //                makePow2(height) != makePow2(this.height))
/*TODO*/  //            {
/*TODO*/  //                createTex = true;
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            this.topaddr     = topaddr;
/*TODO*/  //            this.bufferwidth = bufferwidth;
/*TODO*/  //            this.pixelformat = pixelformat;
/*TODO*/  //            this.sync        = sync;
/*TODO*/  //
/*TODO*/  //            bottomaddr =
/*TODO*/  //                topaddr + bufferwidth * height *
/*TODO*/  //                getPixelFormatBytes(pixelformat);
/*TODO*/  //            getPixels();
/*TODO*/  //
/*TODO*/  //            texS = (float)width / (float)bufferwidth;
/*TODO*/  //            texT = (float)height / (float)makePow2(height);
/*TODO*/  //
/*TODO*/  //            refreshRequired = true;
/*TODO*/  //            display();
/*TODO*/  //
/*TODO*/  //            Emulator.getProcessor().gpr[2] = 0;
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void sceDisplayGetFrameBuf(
/*TODO*/  //        int topaddr, int bufferwidth, int pixelformat, int sync)
/*TODO*/  //    {
/*TODO*/  //        Memory memory = Emulator.getMemory();
/*TODO*/  //        if (!memory.isAddressGood(topaddr    ) ||
/*TODO*/  //            !memory.isAddressGood(bufferwidth) ||
/*TODO*/  //            !memory.isAddressGood(pixelformat) ||
/*TODO*/  //            !memory.isAddressGood(sync))
/*TODO*/  //        {
/*TODO*/  //            Emulator.getProcessor().gpr[2] = -1;
/*TODO*/  //        } else {
/*TODO*/  //            memory.write32(topaddr    , this.topaddr    );
/*TODO*/  //            memory.write32(bufferwidth, this.bufferwidth);
/*TODO*/  //            memory.write32(pixelformat, this.pixelformat);
/*TODO*/  //            memory.write32(sync       , this.sync       );
/*TODO*/  //            Emulator.getProcessor().gpr[2] = 0;
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void sceDisplayGetVcount() {
/*TODO*/  //        // TODO: implement sceDisplayGetVcount
/*TODO*/  //        Emulator.getProcessor().gpr[2] = 0;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void sceDisplayWaitVblankStart() {
/*TODO*/  //        // TODO: implement sceDisplayWaitVblankStart
/*TODO*/  //        ThreadMan.get_instance().ThreadMan_sceKernelDelayThread(0);
/*TODO*/  //        Emulator.getProcessor().gpr[2] = 0;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void sceDisplayWaitVblankStartCB() {
/*TODO*/  //        // TODO: implement sceDisplayWaitVblankStartCB
/*TODO*/  //        Emulator.getProcessor().gpr[2] = 0;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void sceDisplayWaitVblank() {
/*TODO*/  //        // TODO: implement sceDisplayWaitVblank
/*TODO*/  //        ThreadMan.get_instance().ThreadMan_sceKernelDelayThread(0);
/*TODO*/  //        Emulator.getProcessor().gpr[2] = 0;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void sceDisplayWaitVblankCB() {
/*TODO*/  //        // TODO: implement sceDisplayWaitVblankCB
/*TODO*/  //        Emulator.getProcessor().gpr[2] = 0;
/*TODO*/  //    }
/*TODO*/  //}
/*TODO*/  //
