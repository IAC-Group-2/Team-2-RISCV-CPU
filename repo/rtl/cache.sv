/* verilator lint_off UNUSED */
module cache #(
    parameter   ADDRESS_WIDTH = 32,
                DATA_WIDTH = 32, //WIDTH OF THE DATA IN MEM
                BYTE_WIDTH = 8,
                SET_SIZE = 8,
                TAG_SIZE = 22,
                CACHE_WIDTH = 123,
                BYTE_OFFSET_WIDTH = 2,
                WAY_WIDTH = 55

)(
    input   logic                       clk_i,
    
    //input   logic                       wr_en_i, --> replaced with memwritem
    input   logic                       MemWriteM_i,    //write enable
    input   logic [1:0]                 ResultSrcM_i,   //Read enable when ResultSrcM_i = 2'b01
    input   logic [DATA_WIDTH-1:0]      wd_i,
    
    
    //input  logic [2:0]                funct3_i,
    input   logic [ADDRESS_WIDTH-1:0]   addr_i,
    input   logic [DATA_WIDTH-1:0]      data_i,
    output  logic [DATA_WIDTH-1:0]      data_o,

    output  logic                       cache_miss
);
    logic wr_en;
    assign wr_en = MemWriteM_i;
    logic rd_en;
    assign rd_en = ResultSrcM_i == 2'b01;
    logic cache_en;
    assign cache_en = (rd_en || wr_en);
    

    
    // U | V1 | Tag1(22 bits) | Data 1 (32 bits) | V2 | Tag2 (22 bits) | Data 2 (32 bits)
    logic [CACHE_WIDTH-1:0] cache_array [2**SET_SIZE-1:0];
    
    logic [SET_SIZE-1:0] set_addr;
    logic [TAG_SIZE-1:0] tag_addr;

    assign tag_addr = addr_i[ADDRESS_WIDTH -1 : ADDRESS_WIDTH - TAG_SIZE -1];
    assign set_addr = addr_i[SET_SIZE + BYTE_OFFSET_WIDTH -1 : BYTE_WIDTH -1];

    logic cache_valid_0
    logic cache_valid_1

    logic [WAY_SIZE-1:0] cache_way_0;
    logic [WAY_SIZE-1:0] cache_way_1;
    
    logic [TAG_SIZE-1:0] cache_tag_0;
    logic [TAG_SIZE-1:0] cache_tag_1;
    
    logic [DATA_WIDTH-1:0] cache_data_0;
    logic [DATA_WIDTH-1:0] cache_data_1;
    
    
    logic [CACHE_WIDTH-1:0] cache_set;

    assign cache_set = cache_array[set_addr];
    assign cache_way_0 = cache_set[WAY_WIDTH-1:0];
    assign cache_way_1 = cache_set[CACHE_WIDTH - 2: CACHE_WIDTH - 1 - WAY_WIDTH -1];

    assign cache_valid_0 = cache_way_0[WAY_WIDTH-1];
    assign cache_valid_1 = cache_way_1[WAY_WIDTH-1];

    assign cache_tag_0 = cache_way_0[WAY_WIDTH-2: WAY_WIDTH - 2 -TAG_SIZE];
    assign cache_tag_1 = cache_way_1[WAY_WIDTH-2: WAY_WIDTH - 2 -TAG_SIZE];

    assign cache_data_0 = cache_way_0[DATA_WIDTH-1:0];
    assign cache_data_1 = cache_way_1[DATA_WIDTH-1:0];

    logic tag_0_hit;
    logic tag_1_hit;
    logic cache_miss;

    if (cache_en) begin
        
        if (wr_en) begin

        end


        if (rd_en) begin
            
            tag_0_hit = (tag_addr == cache_tag_0 && cache_valid_0);
            tag_1_hit = (tag_addr == cache_tag_1 && cache_valid_1);
            if (tag_0_hit || tag_1_hit) begin
                //hit here
                cache_miss = 0;
                data_o = tag_1_hit ? cache_data_1 : cache_data_0;
            else begin
                cache_miss = 1;


             begin
            
            end

                
            end

        end
    end

    
    // memory read
    always_comb begin
        // funct3 010: load word
        // funct3 000/100: byte
        if (funct3_i == 3'b010) begin // load word
            data_o = {
                ram_array[addr_i[16:0] + 3], 
                ram_array[addr_i[16:0] + 2], 
                ram_array[addr_i[16:0] + 1], 
                ram_array[addr_i[16:0]]
            };
        end else begin // load byte (zero extended)
            data_o = {24'b0, ram_array[addr_i[16:0]]};
        end
    end

    // memory write
    always @(posedge clk_i) begin
        if (wr_en_i) begin
            if (funct3_i == 3'b010) begin // store word
                ram_array[addr_i[16:0]]     <= data_i[7:0];
                ram_array[addr_i[16:0] + 1] <= data_i[15:8];
                ram_array[addr_i[16:0] + 2] <= data_i[23:16];
                ram_array[addr_i[16:0] + 3] <= data_i[31:24];
            end else begin // store byte
                ram_array[addr_i[16:0]] <= data_i[7:0];
            end
        end
    end

endmodule
