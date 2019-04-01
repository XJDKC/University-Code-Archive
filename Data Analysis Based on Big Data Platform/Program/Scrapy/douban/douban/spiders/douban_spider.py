#!/usr/bin/env python
# _*_ coding:utf-8 _*_
import scrapy
import chardet
from douban.items import DouBanItem

class DouBanSpider(scrapy.spiders.Spider):
    name = "DouBan"
    allowed_domains = ["www.baidu.com"]
    start_urls = [
        'https://movie.douban.com/subject/26425063/reviews',
    ]


    def start_requests(self):        
        for url in self.start_urls:
            yield scrapy.Request(url=url,callback=self.parse,dont_filter=True)

    def parse(self, response):
        reviews = response.xpath('//div[@data-cid]/div[@class="main review-item"]')
        

        for review in reviews:
            
            item = DouBanItem()

            item['name'] = review.xpath('.//a[@class="name"]/text()').extract_first()
            item['stars'] = review.xpath('.//span[contains(@class,"allstar")]/@class').extract_first()
            item['date'] = review.xpath('.//span[@class="main-meta"]/text()').extract_first()
            yield item            

        next_page_request = self.requestNextPage(response)
        yield next_page_request


    def requestNextPage(self, response):
        next_page = response.xpath('.//span[@class="next"]/a/@href').extract_first()

        if next_page is not None:
            if next_page != '':
                return scrapy.Request(url=self.start_urls[0]+next_page,callback=self.parse,dont_filter=True)
        return None
